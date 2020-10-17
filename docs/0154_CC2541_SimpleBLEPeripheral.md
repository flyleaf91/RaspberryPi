# CC2541 SimpleBLEPeripheral

理解单片机中的Bluetooth GATT到底是怎么工作的

## 参考文档

* [Capturing_Bluetooth_Host_Controller_Interface_HCI_Logs.pdf](refers/Capturing_Bluetooth_Host_Controller_Interface_HCI_Logs.pdf)
* [CC2541 Mini Development Kit](https://www.ti.com/tool/CC2541DK-MINI)
* [CC253x/4x User's Guide (Rev. F)](https://www.ti.com/lit/ug/swru191f/swru191f.pdf?ts=1602987059730): 单片机数据手册
* [Bluetooth Low Energy software stack](https://www.ti.com/tool/BLE-STACK?DCMP=wbu-blestack&HQS=blestack): BLE-STACK-1-X
* [IAR 8051版本](https://www.iar.com/iar-embedded-workbench/#!?architecture=8051)，个人研究代码，可以考虑破解版
* [SmartRF Flash Programmer v1](http://www.ti.com/tool/flash-programmer)

## SimpleBLEPeripheral 

* [Bluetooth Low Energy software stack](https://www.ti.com/tool/BLE-STACK?DCMP=wbu-blestack&HQS=blestack): BLE-STACK-1-X
  * C:\Texas Instruments\BLE-CC254x-1.5.1.1\Documents
    * **[TI_BLE_Software_Developer's_Guide.pdf](https://www.ti.com/lit/ug/swru271g/swru271g.pdf?ts=1602984402375&ref_url=https%253A%252F%252Fwww.google.com%252F)**
      * CC2540 and CC2541 Bluetooth® low energy Software Developer’s
        * Chapter 8: Development and Debugging
          * 8.3.1 Open an Existing Project
            * open SimpleBLEPeripheral project
          * 8.3.2 Project Options, Configurations, and Defined Symbols
            * 配置IAR直接编译下载调试：[Bluetooth_Development_Kit_UserGuideV24-12461746323.pdf](refers/Bluetooth_Development_Kit_UserGuideV24-12461746323.pdf)
* [CC2541_SoC_Datasheet.pdf](refers/CC2541_SoC_Datasheet.pdf)
  * [CC2540/41 System-on-Chip Solution for 2.4-GHz Bluetooth® low energy Applications](https://www.ti.com/lit/ug/swru191f/swru191f.pdf?ts=1602987059730)
* [IAR 8051版本](https://www.iar.com/iar-embedded-workbench/#!?architecture=8051)，个人研究代码，可以考虑找破解版
* [CC debugger driver on windows 10 (64-bit)](https://e2e.ti.com/support/wireless-connectivity/other-wireless/f/667/t/675493)
* [SimpleBLEPeripheral Key Hack](https://github.com/ZengjfOS/Bluetooth/blob/master/docs/0007_SimpleBLEPeripheral_Key_Hack.md)
* 预编译宏：
  * 右键工程名，选择"Options.." ---> "C/C++ Compiler" ---> "Preprocessor"在"Defined symbols"中添加宏定义
    ```
    INT_HEAP_LEN=3072
    HALNODEBUG
    OSAL_CBTIMER_NUM_TASKS=1
    HAL_AES_DMA=TRUE
    HAL_DMA=TRUE
    POWER_SAVING
    xPLUS_BROADCASTER
    HAL_LCD=FALSE
    HAL_LED=TRUE
    HAL_KEY=TRUE
    CC2540_MINIDK
    ```
* Profile说明
  * Simple Key Profile主要是体现Notification/Indication的工作原理
  * Simple Profile主要是体现read/write的工作原理
* Public MAC: 34:03:DE:16:24:27

## 添加调试串口

* 参考文档
  * [BLE开发（TI CC254x）之串口收发](https://blog.csdn.net/hechao3225/article/details/53931016)
  * [CC2540/CC2541/CC254x之可变参数串口打印配置](https://blog.csdn.net/zzfenglin/article/details/51938856)
* 右键工程名，选择"Options.." ---> "C/C++ Compiler" ---> "Preprocessor"在"Defined symbols"中宏定义如下
  ```
  INT_HEAP_LEN=3072
  HALNODEBUG
  OSAL_CBTIMER_NUM_TASKS=1
  HAL_AES_DMA=TRUE
  HAL_DMA=TRUE
  POWER_SAVING
  xPLUS_BROADCASTER
  HAL_LCD=FALSE
  HAL_LED=TRUE
  HAL_KEY=TRUE
  CC2540_MINIDK
  ```
* 添加：
  * `HAL_UART=TRUE`
  * `ZAPP_P1=TRUE`
  * `NPI_UART_FC=FALSE`
* 关闭：
  * `xPOWER_SAVING`
    * 此宏涉及低功耗控制，如果要开启睡眠模式，还是要打开此宏，开启睡眠模式之后，串口将无法正常使用；
* 添加可变长输出
  ```CPP
  void NPI_PrintString(uint8 *str)  
  {  
    NPI_WriteTransport(str, osal_strlen((char*)str));  
  }  
    
  void NPI_PrintValue(char *title, uint16 value, uint8 format)  
  {  
    uint8 tmpLen;  
    uint8 buf[128];  
    uint32 err;  
    
    tmpLen = (uint8)osal_strlen( (char*)title );  
    osal_memcpy( buf, title, tmpLen );  
    buf[tmpLen] = ' ';  
    err = (uint32)(value);  
    _ltoa( err, &buf[tmpLen+1], format );  
    NPI_PrintString(buf);       
  }
  ```
* 测试串口输出
  ```CPP
  void SimpleBLEPeripheral_Init( uint8 task_id )
  {
    simpleBLEPeripheral_TaskID = task_id;
    
    NPI_InitTransport(NULL);
    // NPI_WriteTransport("Hello World!\r\n", 14);
    NPI_PrintString("Hello World!\r\n");//测试串口发送
  
    // Setup the GAP
    VOID GAP_SetParamValue( TGAP_CONN_PAUSE_PERIPHERAL, DEFAULT_CONN_PAUSE_PERIPHERAL );
  
    //...省略
  }
  ```
* 注意在`SimpleBLEPeripheral_Init()`后面重新初始化了`P0`端口，会导致`UART0`输出出问题，需要调整；
  * `P0SEL = 0 | 0x01 << 2 | 0x01 << 3; // Configure Port 0 as GPIO`
* 模仿`printf()`
  ```CPP
  #include "OSAL.h"
  #include <stdarg.h>
  #include <stdio.h>
  #define DEBUG_PRINT

  void NPI_PrintValue(const char* fmt, ...)
  {
  #ifdef DEBUG_PRINT
  	va_list ap;
  	uint8 buffer[100];
  	uint16 len;
  	
  	va_start(ap,fmt);
  	len = vsprintf((char *)buffer,fmt,ap);
  	va_end(ap);

  	NPI_WriteTransport(buffer,len);
  	//NPI_WriteTransport("\r\n",osal_strlen("\r\n"));
  #else
  	return;
  #endif
  }
  ```
  * 可以将上面的代码放入`npi`代码中，方便在各处进行调用


## 启动BLE广播

* S1(P0.1)启动广播按键处理流程：
  ```
  * int main(void)
    * HalDriverInit();
      * HalKeyInit();
        * #if defined ( CC2540_MINIDK )
          * HAL_KEY_SW_2_SEL &= ~(HAL_KEY_SW_1_BIT);    /* Set pin function to GPIO */
          * HAL_KEY_SW_2_DIR &= ~(HAL_KEY_SW_1_BIT);    /* Set pin direction to Input */
          * PICTL |= HAL_KEY_SW_1_EDGEBIT;   /* Set the edge bit to set falling edge to give int */
          * HAL_KEY_SW_1_IEN |= ( HAL_KEY_SW_1_IENBIT | HAL_KEY_SW_2_IENBIT );   /* enable CPU interrupt */
    * osal_init_system();
      * osalInitTasks();
        * Hal_Init( taskID++ );                                                           --> task id = 1，这个id是固定分配的，和tasksArr[]数组对应的函数处理
          * Hal_TaskID = task_id;                                                         --> 初始化任务ID
            * const pTaskEventHandlerFn tasksArr[]
              * Hal_ProcessEvent,                               // task 1                 --> task id = 1
                * uint16 Hal_ProcessEvent( uint8 task_id, uint16 events )
                  * if (events & HAL_KEY_EVENT)
                    * HalKeyPoll();
                      * #if defined (CC2540_MINIDK)
                        * keys |= HAL_KEY_SW_2;
                      * if (notify && (pHalKeyProcessFunction))
                        * (pHalKeyProcessFunction) (keys, HAL_KEY_STATE_NORMAL);          --> 调用注册回调函数来处理
                    * return events ^ HAL_KEY_EVENT;
        * SimpleBLEPeripheral_Init( taskID );
          * simpleBLEPeripheral_TaskID = task_id;
            * #if defined( CC2540_MINIDK )
              * RegisterForKeys( simpleBLEPeripheral_TaskID );
                * registeredKeysTaskID = task_id;
                  * const pTaskEventHandlerFn tasksArr[]
                    * SimpleBLEPeripheral_ProcessEvent                                  // task 11
                      * uint16 SimpleBLEPeripheral_ProcessEvent( uint8 task_id, uint16 events )
                        * if ( events & SYS_EVENT_MSG )
                          * if ( (pMsg = osal_msg_receive( simpleBLEPeripheral_TaskID )) != NULL )
                            * simpleBLEPeripheral_ProcessOSALMsg( (osal_event_hdr_t *)pMsg );
                              * switch ( pMsg->event )
                                * case KEY_CHANGE:
                                  * simpleBLEPeripheral_HandleKeys( ((keyChange_t *)pMsg)->state, ((keyChange_t *)pMsg)->keys );
                                    * if ( keys & HAL_KEY_SW_2 )
                                      * SK_Keys |= SK_KEY_RIGHT;
                                        * GAPRole_GetParameter( GAPROLE_ADVERT_ENABLED, &current_adv_enabled_status );
                                        * GAPRole_SetParameter( GAPROLE_ADVERT_ENABLED, sizeof( uint8 ), &new_adv_enabled_status );       --> 开始广播
                                          * case GAPROLE_ADVERT_ENABLED:
                                            * VOID osal_set_event( gapRole_TaskID, START_ADVERTISING_EVT );
                                              * 接下来又GAP事件处理任务进行处理开始广播
                                    * SK_SetParameter( SK_KEY_ATTR, sizeof ( uint8 ), &SK_Keys );                                         --> 按键通知
                                      * case SK_KEY_ATTR:
                                        * skKeyPressed = *((uint8*)pValue);
                                        * GATTServApp_ProcessCharCfg( skConfig, &skKeyPressed, FALSE, simplekeysAttrTbl, GATT_NUM_ATTRS( simplekeysAttrTbl ), INVALID_TASK_ID, sk_ReadAttrCB );
                                          * &skKeyPressed: 通过传入这个地址，从而知道所在的simplekeysAttrTbl的位置
    * InitBoard( OB_READY );
      * OnboardKeyIntEnable = HAL_KEY_INTERRUPT_ENABLE;
      * HalKeyConfig( OnboardKeyIntEnable, OnBoard_KeyCallback);
        * Hal_KeyIntEnable = interruptEnable;
        * pHalKeyProcessFunction = cback;                                                 --> 设置前面的回调函数
          * void OnBoard_KeyCallback ( uint8 keys, uint8 state )
            * OnBoard_SendKeys( keys, shift ) != SUCCESS
              * msgPtr = (keyChange_t *)osal_msg_allocate( sizeof(keyChange_t) );
              * msgPtr->hdr.event = KEY_CHANGE;
              * msgPtr->state = state;
              * msgPtr->keys = keys;
              * osal_msg_send( registeredKeysTaskID, (uint8 *)msgPtr );
  * HAL_ISR_FUNCTION( halKeyPort0Isr, P0INT_VECTOR )                                      --> 注册中断映射处理函数
    * halProcessKeyInterrupt();
      * #if defined ( CC2540_MINIDK )
        * HAL_KEY_SW_2_PXIFG = ~(HAL_KEY_SW_2_BIT); /* Clear Interrupt Flag */
          * #define HAL_KEY_SW_2_PXIFG    P0IFG /* Interrupt flag at source */
        * valid = TRUE;
        * osal_start_timerEx (Hal_TaskID, HAL_KEY_EVENT, HAL_KEY_DEBOUNCE_VALUE);         --> 通过任务ID调度任务
  ```
  * 由上可知，操作系统的`task id`是启动的时候就和任务数组一一对应起来的，认识这一点对分析代码会快一点；
* C:\Texas Instruments\BLE-CC254x-1.5.1.1\Components\hal\common\hal_drivers.c
* 处理流程：中断 --> HAL task --> SimpleBLEPeripheral task --> GAP task 


## 按键服务处理流程

### Key Service

```cpp
/*********************************************************************
 * Profile Attributes - Table
 */
static gattAttribute_t simplekeysAttrTbl[SERVAPP_NUM_ATTR_SUPPORTED] = 
{
  // Simple Keys Service，服务声明
  { 
    { ATT_BT_UUID_SIZE, primaryServiceUUID }, /* type */
    GATT_PERMIT_READ,                         /* permissions */
    0,                                        /* handle */
    (uint8 *)&skService                       /* pValue */
  },
    // Characteristic Declaration for Keys，特征权限声明
    { 
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ, 
      0,
      &skCharProps 
    },
      // Characteristic Value- Key Pressed，存储特征值
      { 
        { ATT_BT_UUID_SIZE, keyPressedUUID },
        0, 
        0, 
        &skKeyPressed 
      },
      // Characteristic configuration，通过名为"客户端特性配置描述符（Client Characteristic Configuration Descriptor，CCCD）"的特定描述符来开启或关闭通知（NOTIFY）信息。
      { 
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
        0, 
        (uint8 *)&skConfig 
      },
      // Characteristic User Description，特征描述
      { 
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ, 
        0, 
        skCharUserDesp 
      },      
};
```

### GATT按键处理

```
* int main(void)
  * osal_init_system();
    * osalInitTasks();
      * SimpleBLEPeripheral_Init( taskID );
        * simpleBLEPeripheral_TaskID = task_id;
          * #if defined( CC2540_MINIDK )
            * RegisterForKeys( simpleBLEPeripheral_TaskID );
              * registeredKeysTaskID = task_id;
                * const pTaskEventHandlerFn tasksArr[]
                  * SimpleBLEPeripheral_ProcessEvent                                  // task 11
                    * uint16 SimpleBLEPeripheral_ProcessEvent( uint8 task_id, uint16 events )
                      * if ( events & SYS_EVENT_MSG )
                        * if ( (pMsg = osal_msg_receive( simpleBLEPeripheral_TaskID )) != NULL )
                          * simpleBLEPeripheral_ProcessOSALMsg( (osal_event_hdr_t *)pMsg );
                            * switch ( pMsg->event )
                              * case KEY_CHANGE:
                                * simpleBLEPeripheral_HandleKeys( ((keyChange_t *)pMsg)->state, ((keyChange_t *)pMsg)->keys );
                                  * if ( keys & HAL_KEY_SW_2 )
                                    * SK_Keys |= SK_KEY_RIGHT;
                                      * GAPRole_GetParameter( GAPROLE_ADVERT_ENABLED, &current_adv_enabled_status );
                                      * GAPRole_SetParameter( GAPROLE_ADVERT_ENABLED, sizeof( uint8 ), &new_adv_enabled_status );       --> 开始广播
                                        * case GAPROLE_ADVERT_ENABLED:
                                          * VOID osal_set_event( gapRole_TaskID, START_ADVERTISING_EVT );
                                            * 接下来又GAP事件处理任务进行处理开始广播
                                  * SK_SetParameter( SK_KEY_ATTR, sizeof ( uint8 ), &SK_Keys );                                         --> 按键通知
                                    * case SK_KEY_ATTR:
                                      * skKeyPressed = *((uint8*)pValue);
                                      * GATTServApp_ProcessCharCfg( skConfig, &skKeyPressed, FALSE, simplekeysAttrTbl, GATT_NUM_ATTRS( simplekeysAttrTbl ), INVALID_TASK_ID, sk_ReadAttrCB );
                                        * pAttr = GATTServApp_FindAttr( attrTbl, numAttrs, pValue );
                                          * if ( pAttrTbl[i].pValue == pValue )
                                            * &skKeyPressed: 通过传入这个地址，从而知道所在的simplekeysAttrTbl的位置
                                        * if ( pItem->value & GATT_CLIENT_CFG_NOTIFY )
                                          * status |= gattServApp_SendNotiInd( pItem->connHandle, GATT_CLIENT_CFG_NOTIFY, authenticated, pAttr, taskId, pfnReadAttrCB );
                                            * noti.pValue = (uint8 *)GATT_bm_alloc( connHandle, ATT_HANDLE_VALUE_NOTI, GATT_MAX_MTU, &len );
                                            * status = (*pfnReadAttrCB)( connHandle, pAttr, noti.pValue, &noti.len, 0, len, GATT_LOCAL_READ );
                                              * static bStatus_t sk_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen, uint8 method )
                                                * 这里相当于回调用户自己写的数据拷贝函数sk_ReadAttrCB()
                                            * status = GATT_Notification( connHandle, &noti, authenticated );                           --> 到这里数据就发出去了
                                        * if ( pItem->value & GATT_CLIENT_CFG_INDICATE )
                                          * status |= gattServApp_SendNotiInd( pItem->connHandle, GATT_CLIENT_CFG_INDICATE, authenticated, pAttr, taskId, pfnReadAttrCB );
        * GATTServApp_AddService( GATT_ALL_SERVICES );    // GATT attributes
        * DevInfo_AddService();                           // Device Information Service
          * return GATTServApp_RegisterService( devInfoAttrTbl, GATT_NUM_ATTRS( devInfoAttrTbl ), GATT_MAX_ENCRYPT_KEY_SIZE, &devInfoCBs );
        * SimpleProfile_AddService( GATT_ALL_SERVICES );  // Simple GATT Profile
          * GATTServApp_InitCharCfg( INVALID_CONNHANDLE, simpleProfileChar4Config );
          * status = GATTServApp_RegisterService( simpleProfileAttrTbl, GATT_NUM_ATTRS( simpleProfileAttrTbl ), GATT_MAX_ENCRYPT_KEY_SIZE, &simpleProfileCBs );
        * SK_AddService( GATT_ALL_SERVICES ); // Simple Keys Profile
          * skConfig = (gattCharCfg_t *)osal_mem_alloc( sizeof(gattCharCfg_t) * linkDBNumConns );
            * linkDBNumConns: 表示连接的设备数
          * GATTServApp_InitCharCfg( INVALID_CONNHANDLE, skConfig ); 
          * status = GATTServApp_RegisterService( simplekeysAttrTbl, GATT_NUM_ATTRS( simplekeysAttrTbl ), GATT_MAX_ENCRYPT_KEY_SIZE, &skCBs );
            * simplekeysAttrTbl
              * // Characteristic Value- Key Pressed
                * { ATT_BT_UUID_SIZE, keyPressedUUID },
                * &skKeyPressed 
              * // Characteristic configuration
                * (uint8 *)&skConfig 
            * &skCBs
              * CONST gattServiceCBs_t skCBs
                * sk_ReadAttrCB,  // Read callback function pointer
                  * static bStatus_t sk_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen, uint8 method )
                    * connHandle: Handle of current connection。一个BLE可能被多个设备连接，所以这个需要靠这个句柄来区分不同的设备
                    * uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
                    * switch ( uuid )
                      * case SK_KEYPRESSED_UUID:
                        * pValue[0] = *pAttr->pValue;
                          * 按键数据在这里进行拷贝
                * sk_WriteAttrCB, // Write callback function pointer
                  * 暂时未使用
```

## 配对密码

`uint32 passkey = 0; // passkey "000000"`

```CPP
void SimpleBLEPeripheral_Init( uint8 task_id ) {
  //...省略

  // Setup the GAP Bond Manager
  {
    uint32 passkey = 0; // passkey "000000"
    uint8 pairMode = GAPBOND_PAIRING_MODE_WAIT_FOR_REQ;
    uint8 mitm = TRUE;
    uint8 ioCap = GAPBOND_IO_CAP_DISPLAY_ONLY;
    uint8 bonding = TRUE;
    GAPBondMgr_SetParameter( GAPBOND_DEFAULT_PASSCODE, sizeof ( uint32 ), &passkey );
    GAPBondMgr_SetParameter( GAPBOND_PAIRING_MODE, sizeof ( uint8 ), &pairMode );
    GAPBondMgr_SetParameter( GAPBOND_MITM_PROTECTION, sizeof ( uint8 ), &mitm );
    GAPBondMgr_SetParameter( GAPBOND_IO_CAPABILITIES, sizeof ( uint8 ), &ioCap );
    GAPBondMgr_SetParameter( GAPBOND_BONDING_ENABLED, sizeof ( uint8 ), &bonding );
  }

  //...省略
}
```

## 蓝牙扫描名称

```CPP
// GAP - SCAN RSP data (max size = 31 bytes)
static uint8 scanRspData[] =
{
  // complete name
  0x14,   // length of this data
  GAP_ADTYPE_LOCAL_NAME_COMPLETE,
  0x53,   // 'S'
  0x69,   // 'i'
  0x6d,   // 'm'
  0x70,   // 'p'
  0x6c,   // 'l'
  0x65,   // 'e'
  0x42,   // 'B'
  0x4c,   // 'L'
  0x45,   // 'E'
  0x50,   // 'P'
  0x65,   // 'e'
  0x72,   // 'r'
  0x69,   // 'i'
  0x70,   // 'p'
  0x68,   // 'h'
  0x65,   // 'e'
  0x72,   // 'r'
  0x61,   // 'a'
  0x6c,   // 'l'

  // connection interval range
  0x05,   // length of this data
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE,
  LO_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ),   // 100ms
  HI_UINT16( DEFAULT_DESIRED_MIN_CONN_INTERVAL ),
  LO_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ),   // 1s
  HI_UINT16( DEFAULT_DESIRED_MAX_CONN_INTERVAL ),

  // Tx power level
  0x02,   // length of this data
  GAP_ADTYPE_POWER_LEVEL,
  0       // 0dBm
};
```

## 广播数据

```CPP
// GAP - Advertisement data (max size = 31 bytes, though this is
// best kept short to conserve power while advertisting)
static uint8 advertData[] =
{
  // Flags; this sets the device to use limited discoverable
  // mode (advertises for 30 seconds at a time) instead of general
  // discoverable mode (advertises indefinitely)
  0x02,   // length of this data
  GAP_ADTYPE_FLAGS,
  DEFAULT_DISCOVERABLE_MODE | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,

  // service UUID, to notify central devices what services are included
  // in this peripheral
  0x03,   // length of this data
  GAP_ADTYPE_16BIT_MORE,      // some of the UUID's, but not all
  LO_UINT16( SIMPLEPROFILE_SERV_UUID ),
  HI_UINT16( SIMPLEPROFILE_SERV_UUID ),

};
```

## MAC地址

```CPP
static void peripheralStateNotificationCB( gaprole_States_t newState ) 
{
#ifdef PLUS_BROADCASTER
  static uint8 first_conn_flag = 0;
#endif // PLUS_BROADCASTER
  
  
  switch ( newState )
  {
    case GAPROLE_STARTED:
      {
        uint8 ownAddress[B_ADDR_LEN];
        uint8 systemId[DEVINFO_SYSTEM_ID_LEN];

        GAPRole_GetParameter(GAPROLE_BD_ADDR, ownAddress);

        // use 6 bytes of device address for 8 bytes of system ID value
        systemId[0] = ownAddress[0];
        systemId[1] = ownAddress[1];
        systemId[2] = ownAddress[2];

        // set middle bytes to zero
        systemId[4] = 0x00;
        systemId[3] = 0x00;

        // shift three bytes up
        systemId[7] = ownAddress[5];
        systemId[6] = ownAddress[4];
        systemId[5] = ownAddress[3];

        DevInfo_SetParameter(DEVINFO_SYSTEM_ID, DEVINFO_SYSTEM_ID_LEN, systemId);

        // ..省略
      }

    // ..省略
  }

  // ..省略
}
```

## 绑定任务

```
* int main(void)
  * osal_init_system();
    * osalInitTasks();
      * SimpleBLEPeripheral_Init( taskID );
        * osal_set_event( simpleBLEPeripheral_TaskID, SBP_START_DEVICE_EVT );
  * osal_start_system(); // No Return from here
    * osal_run_system();
      * events = (tasksArr[idx])( idx, events );
        * GAPBondMgr_ProcessEvent,                                          // task 9
          * if ( events & SYS_EVENT_MSG )
            * if ( (pMsg = osal_msg_receive( gapBondMgr_TaskID )) != NULL )
              * if ( gapBondMgr_ProcessOSALMsg( (osal_event_hdr_t *)pMsg ) )
                * switch ( pMsg->event )
                  * case GAP_MSG_EVENT:                                                               // 处理GAP事件
                    * switch ( pMsg->opcode )
                      * case GAP_PASSKEY_NEEDED_EVENT:
                        * if ( GAP_PasscodeUpdate( gapBond_Passcode, pPkt->connectionHandle ) != SUCCESS )
                          * static uint32 gapBond_Passcode = 0;
                            * bStatus_t GAPBondMgr_SetParameter( uint16 param, uint8 len, void *pValue )
                              * case GAPBOND_DEFAULT_PASSCODE:
                                * gapBond_Passcode = *((uint32*)pValue);
                                  * GAPBondMgr_SetParameter( GAPBOND_DEFAULT_PASSCODE, sizeof ( uint32 ), &passkey );
                                    * uint32 passkey = 0; // passkey "000000"
                                      * //! Maximum Pairing Passcode/Passkey value.  Range of a passkey can be 0 - 999,999.
                                        * 如上一个unit32就够用来保存passkey，其实只用到了低3 byte；
                  * case GATT_MSG_EVENT:
                    * 暂时来看，没什么需要处理的
                  * case GATT_SERV_MSG_EVENT:
        * SimpleBLEPeripheral_ProcessEvent                                  // task 11
          * if ( events & SBP_START_DEVICE_EVT )
            * VOID GAPRole_StartDevice( &simpleBLEPeripheral_PeripheralCBs );
              * &simpleBLEPeripheral_PeripheralCBs
                * static gapRolesCBs_t simpleBLEPeripheral_PeripheralCBs
                  * case GAPROLE_STARTED:
                    * GAPRole_GetParameter(GAPROLE_BD_ADDR, ownAddress);                            // 获取MAC地址，地址是静态的
                  * case GAPROLE_ADVERTISING:
                    * HalLcdWriteString( "Advertising",  HAL_LCD_LINE_3 );
                  * case GAPROLE_CONNECTED:
                    * GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8), &advertEnabled);  // disable
              * bStatus_t GAPRole_StartDevice( gapRolesCBs_t *pAppCallbacks )
            * VOID GAPBondMgr_Register( &simpleBLEPeripheral_BondMgrCBs );
              * &simpleBLEPeripheral_BondMgrCBs
                * static gapBondCBs_t simpleBLEPeripheral_BondMgrCBs
                  * NULL
                  * NULL
              * void GAPBondMgr_Register( gapBondCBs_t *pCB )
                * OID GAP_SetParamValue( TGAP_AUTH_TASK_ID, gapBondMgr_TaskID );
                  * // Take over the processing of Authentication messages
                    * 从以上可知，绑定是GAP发出的事件，有绑定处理程序去处理
                * GATTServApp_RegisterForMsg( gapBondMgr_TaskID );
                  * 绑定处理程序还要处理GATT发出的事件
            * osal_start_timerEx( simpleBLEPeripheral_TaskID, SBP_PERIODIC_EVT, SBP_PERIODIC_EVT_PERIOD );
```

## gatttool

在不配对的情况下也能使用，暂时不知道为什么

```
pi@raspberrypi:~ $ sudo gatttool -b 34:03:DE:16:24:27 -I
[34:03:DE:16:24:27][LE]> connect
Attempting to connect to 34:03:DE:16:24:27
Connection successful
[34:03:DE:16:24:27][LE]> primary
attr handle: 0x0001, end grp handle: 0x000b uuid: 00001800-0000-1000-8000-00805f9b34fb
attr handle: 0x000c, end grp handle: 0x000f uuid: 00001801-0000-1000-8000-00805f9b34fb
attr handle: 0x0010, end grp handle: 0x0022 uuid: 0000180a-0000-1000-8000-00805f9b34fb
attr handle: 0x0023, end grp handle: 0x0033 uuid: 0000fff0-0000-1000-8000-00805f9b34fb
attr handle: 0x0034, end grp handle: 0xffff uuid: 0000ffe0-0000-1000-8000-00805f9b34fb
[34:03:DE:16:24:27][LE]> characteristics
handle: 0x0002, char properties: 0x02, char value handle: 0x0003, uuid: 00002a00-0000-1000-8000-00805f9b34fb
handle: 0x0004, char properties: 0x02, char value handle: 0x0005, uuid: 00002a01-0000-1000-8000-00805f9b34fb
handle: 0x0006, char properties: 0x02, char value handle: 0x0007, uuid: 00002a02-0000-1000-8000-00805f9b34fb
handle: 0x0008, char properties: 0x08, char value handle: 0x0009, uuid: 00002a03-0000-1000-8000-00805f9b34fb
handle: 0x000a, char properties: 0x02, char value handle: 0x000b, uuid: 00002a04-0000-1000-8000-00805f9b34fb
handle: 0x000d, char properties: 0x20, char value handle: 0x000e, uuid: 00002a05-0000-1000-8000-00805f9b34fb
handle: 0x0011, char properties: 0x02, char value handle: 0x0012, uuid: 00002a23-0000-1000-8000-00805f9b34fb
handle: 0x0013, char properties: 0x02, char value handle: 0x0014, uuid: 00002a24-0000-1000-8000-00805f9b34fb
handle: 0x0015, char properties: 0x02, char value handle: 0x0016, uuid: 00002a25-0000-1000-8000-00805f9b34fb
handle: 0x0017, char properties: 0x02, char value handle: 0x0018, uuid: 00002a26-0000-1000-8000-00805f9b34fb
handle: 0x0019, char properties: 0x02, char value handle: 0x001a, uuid: 00002a27-0000-1000-8000-00805f9b34fb
handle: 0x001b, char properties: 0x02, char value handle: 0x001c, uuid: 00002a28-0000-1000-8000-00805f9b34fb
handle: 0x001d, char properties: 0x02, char value handle: 0x001e, uuid: 00002a29-0000-1000-8000-00805f9b34fb
handle: 0x001f, char properties: 0x02, char value handle: 0x0020, uuid: 00002a2a-0000-1000-8000-00805f9b34fb
handle: 0x0021, char properties: 0x02, char value handle: 0x0022, uuid: 00002a50-0000-1000-8000-00805f9b34fb
handle: 0x0024, char properties: 0x0a, char value handle: 0x0025, uuid: 0000fff1-0000-1000-8000-00805f9b34fb
handle: 0x0027, char properties: 0x02, char value handle: 0x0028, uuid: 0000fff2-0000-1000-8000-00805f9b34fb
handle: 0x002a, char properties: 0x08, char value handle: 0x002b, uuid: 0000fff3-0000-1000-8000-00805f9b34fb
handle: 0x002d, char properties: 0x10, char value handle: 0x002e, uuid: 0000fff4-0000-1000-8000-00805f9b34fb
handle: 0x0031, char properties: 0x02, char value handle: 0x0032, uuid: 0000fff5-0000-1000-8000-00805f9b34fb
handle: 0x0035, char properties: 0x10, char value handle: 0x0036, uuid: 0000ffe1-0000-1000-8000-00805f9b34fb
[34:03:DE:16:24:27][LE]> char-read-hnd 0x0025
Characteristic value/descriptor: 01
[34:03:DE:16:24:27][LE]> char-read-hnd 0x0028
Characteristic value/descriptor: 02
[34:03:DE:16:24:27][LE]> char-read-uuid fff1
handle: 0x0025   value: 01
[34:03:DE:16:24:27][LE]> char-read-uuid fff2
handle: 0x0028   value: 02
[34:03:DE:16:24:27][LE]> char-read-hnd 0x0003
Characteristic value/descriptor: 53 69 6d 70 6c 65 20 42 4c 45 20 50 65 72 69 70 68 65 72 61 6c
[34:03:DE:16:24:27][LE]> char-read-hnd 0x000f
Characteristic value/descriptor: 02 00

```

## bluez

* sudo btmgmt
  * power off
  * bredr off
  * power on
* sudo btmon 2>&1 | tee btmon.log
* sudo bluetoothctl
  * remove 34:03:DE:16:24:27
  * scan on
    * [NEW] Device 34:03:DE:16:24:27 SimpleBLEPeripheral
  * scan off
  * devices
    * Device 34:03:DE:16:24:27 SimpleBLEPeripheral
  * pair 34:03:DE:16:24:27
    * passkey: `000000`

pair log:

```
Attempting to pair with 34:03:DE:16:24:27
[CHG] Device 34:03:DE:16:24:27 Connected: yes
Request passkey
[agent] Enter passkey (number in 0-999999): [NEW] Primary Service
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service000c
        00001801-0000-1000-8000-00805f9b34fb
        Generic Attribute Profile
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service000c/char000d
        00002a05-0000-1000-8000-00805f9b34fb
        Service Changed
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service000c/char000d/desc000f
        00002902-0000-1000-8000-00805f9b34fb
        Client Characteristic Configuration
[NEW] Primary Service
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010
        0000180a-0000-1000-8000-00805f9b34fb
        Device Information
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char0011
        00002a23-0000-1000-8000-00805f9b34fb
        System ID
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char0013
        00002a24-0000-1000-8000-00805f9b34fb
        Model Number String
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char0015
        00002a25-0000-1000-8000-00805f9b34fb
        Serial Number String
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char0017
        00002a26-0000-1000-8000-00805f9b34fb
        Firmware Revision String
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char0019
        00002a27-0000-1000-8000-00805f9b34fb
        Hardware Revision String
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char001b
        00002a28-0000-1000-8000-00805f9b34fb
        Software Revision String
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char001d
        00002a29-0000-1000-8000-00805f9b34fb
        Manufacturer Name String
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char001f
        00002a2a-0000-1000-8000-00805f9b34fb
        IEEE 11073-20601 Regulatory Cert. Data List
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0010/char0021
        00002a50-0000-1000-8000-00805f9b34fb
        PnP ID
[NEW] Primary Service
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023
        0000fff0-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char0024
        0000fff1-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char0024/desc0026
        00002901-0000-1000-8000-00805f9b34fb
        Characteristic User Description
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char0027
        0000fff2-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char0027/desc0029
        00002901-0000-1000-8000-00805f9b34fb
        Characteristic User Description
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char002a
        0000fff3-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char002a/desc002c
        00002901-0000-1000-8000-00805f9b34fb
        Characteristic User Description
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char002d
        0000fff4-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char002d/desc002f
        00002902-0000-1000-8000-00805f9b34fb
        Client Characteristic Configuration
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char002d/desc0030
        00002901-0000-1000-8000-00805f9b34fb
        Characteristic User Description
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char0031
        0000fff5-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0023/char0031/desc0033
        00002901-0000-1000-8000-00805f9b34fb
        Characteristic User Description
[NEW] Primary Service
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0034
        0000ffe0-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Characteristic
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0034/char0035
        0000ffe1-0000-1000-8000-00805f9b34fb
        Unknown
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0034/char0035/desc0037
        00002902-0000-1000-8000-00805f9b34fb
        Client Characteristic Configuration
[NEW] Descriptor
        /org/bluez/hci0/dev_34_03_DE_16_24_27/service0034/char0035/desc0038
        00002901-0000-1000-8000-00805f9b34fb
        Characteristic User Description
[CHG] Device 34:03:DE:16:24:27 UUIDs: 00001800-0000-1000-8000-00805f9b34fb
[CHG] Device 34:03:DE:16:24:27 UUIDs: 00001801-0000-1000-8000-00805f9b34fb
[CHG] Device 34:03:DE:16:24:27 UUIDs: 0000180a-0000-1000-8000-00805f9b34fb
[CHG] Device 34:03:DE:16:24:27 UUIDs: 0000ffe0-0000-1000-8000-00805f9b34fb
[CHG] Device 34:03:DE:16:24:27 UUIDs: 0000fff0-0000-1000-8000-00805f9b34fb
[CHG] Device 34:03:DE:16:24:27 ServicesResolved: yes
[CHG] Device 34:03:DE:16:24:27 Name: Simple BLE Peripheral
[CHG] Device 34:03:DE:16:24:27 Alias: Simple BLE Peripheral
[CHG] Device 34:03:DE:16:24:27 Modalias: bluetooth:v000Dp0000d0110
000000
[CHG] Device 34:03:DE:16:24:27 Paired: yes
Pairing successful
```
  
btmon log如下：

```
Bluetooth monitor ver 5.50
= Note: Linux version 4.19.122-v7l (armv7l)                            0.641145
= Note: Bluetooth subsystem version 2.22                               0.641180
= New Index: DC:A6:32:B2:F8:FF (Primary,UART,hci0)              [hci0] 0.641183
= Open Index: DC:A6:32:B2:F8:FF                                 [hci0] 0.641186
= Index Info: DC:A6:32:B.. (Cypress Semiconductor Corporation)  [hci0] 0.641189
@ MGMT Open: btmgmt (privileged) version 1.14                 {0x0002} 0.641193
@ MGMT Open: bluetoothd (privileged) version 1.14             {0x0001} 0.641195
@ MGMT Open: btmon (privileged) version 1.14                  {0x0003} 0.641462
@ MGMT Command: Pair Device (0x0019) plen 8            {0x0001} [hci0] 7.189699
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)                               # pair的设备
        Capability: KeyboardDisplay (0x04)                                              # 设备配对能力
< HCI Command: LE Set Scan Parameters (0x08|0x000b) plen 7   #1 [hci0] 7.189788         # 设置扫描参数
        Type: Passive (0x00)
        Interval: 60.000 msec (0x0060)
        Window: 30.000 msec (0x0030)
        Own address type: Public (0x00)
        Filter policy: Ignore not in white list (0x01)
> HCI Event: Command Complete (0x0e) plen 4                  #2 [hci0] 7.190122
      LE Set Scan Parameters (0x08|0x000b) ncmd 1
        Status: Success (0x00)
< HCI Command: LE Set Scan Enable (0x08|0x000c) plen 2       #3 [hci0] 7.190180         # 开始扫描
        Scanning: Enabled (0x01)
        Filter duplicates: Enabled (0x01)
> HCI Event: Command Complete (0x0e) plen 4                  #4 [hci0] 7.190572
      LE Set Scan Enable (0x08|0x000c) ncmd 1
        Status: Success (0x00)
> HCI Event: LE Meta Event (0x3e) plen 19                    #5 [hci0] 7.221156         # 发现设备，正好是: advertData数据
      LE Advertising Report (0x02)
        Num reports: 1
        Event type: Connectable undirected - ADV_IND (0x00)
        Address type: Public (0x00)
        Address: 34:03:DE:16:24:27 (Texas Instruments)
        Data length: 7
        Flags: 0x05                                                                     # DEFAULT_DISCOVERABLE_MODE | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
          LE Limited Discoverable Mode
          BR/EDR Not Supported
        16-bit Service UUIDs (partial): 1 entry
          Unknown (0xfff0)                                                              # SIMPLEPROFILE_SERV_UUID
        RSSI: -61 dBm (0xc3)
< HCI Command: LE Set Scan Enable (0x08|0x000c) plen 2       #6 [hci0] 7.221221         # 关闭扫描
        Scanning: Disabled (0x00)
        Filter duplicates: Disabled (0x00)
> HCI Event: Command Complete (0x0e) plen 4                  #7 [hci0] 7.223636
      LE Set Scan Enable (0x08|0x000c) ncmd 1
        Status: Success (0x00)
< HCI Command: LE Create Connection (0x08|0x000d) plen 25    #8 [hci0] 7.223682         # 开始连接，带连接参数
        Scan interval: 60.000 msec (0x0060)
        Scan window: 60.000 msec (0x0060)
        Filter policy: White list is not used (0x00)
        Peer address type: Public (0x00)
        Peer address: 34:03:DE:16:24:27 (Texas Instruments)
        Own address type: Public (0x00)
        Min connection interval: 30.00 msec (0x0018)
        Max connection interval: 50.00 msec (0x0028)
        Connection latency: 0 (0x0000)
        Supervision timeout: 420 msec (0x002a)
        Min connection length: 0.000 msec (0x0000)
        Max connection length: 0.000 msec (0x0000)
> HCI Event: Command Status (0x0f) plen 4                    #9 [hci0] 7.224258
      LE Create Connection (0x08|0x000d) ncmd 1
        Status: Success (0x00)
> HCI Event: LE Meta Event (0x3e) plen 19                   #10 [hci0] 7.333133         # 连接成功
      LE Connection Complete (0x01)
        Status: Success (0x00)
        Handle: 64
        Role: Master (0x00)
        Peer address type: Public (0x00)
        Peer address: 34:03:DE:16:24:27 (Texas Instruments)
        Connection interval: 48.75 msec (0x0027)
        Connection latency: 0 (0x0000)
        Supervision timeout: 420 msec (0x002a)
        Master clock accuracy: 0x00
@ MGMT Event: Device Connected (0x000b) plen 20        {0x0003} [hci0] 7.333189
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Flags: 0x00000000
        Data length: 7
        Flags: 0x05
          LE Limited Discoverable Mode
          BR/EDR Not Supported
        16-bit Service UUIDs (partial): 1 entry
          Unknown (0xfff0)
@ MGMT Event: Device Connected (0x000b) plen 20        {0x0002} [hci0] 7.333189
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Flags: 0x00000000
        Data length: 7
        Flags: 0x05
          LE Limited Discoverable Mode
          BR/EDR Not Supported
        16-bit Service UUIDs (partial): 1 entry
          Unknown (0xfff0)
@ MGMT Event: Device Connected (0x000b) plen 20        {0x0001} [hci0] 7.333189
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Flags: 0x00000000
        Data length: 7
        Flags: 0x05
          LE Limited Discoverable Mode
          BR/EDR Not Supported
        16-bit Service UUIDs (partial): 1 entry
          Unknown (0xfff0)
< HCI Command: LE Read Remote Used... (0x08|0x0016) plen 2  #11 [hci0] 7.333394         # 暂时还是不知道这个干啥用的
        Handle: 64
> HCI Event: Command Status (0x0f) plen 4                   #12 [hci0] 7.334720
      LE Read Remote Used Features (0x08|0x0016) ncmd 1
        Status: Success (0x00)
> HCI Event: Command Complete (0x0e) plen 14                #13 [hci0] 7.334734
      LE Read Remote Used Features (0x08|0x0016) ncmd 1
        Status: Success (0x00)
        00 00 00 00 00 00 00 00 00 00                    ..........      
> HCI Event: LE Meta Event (0x3e) plen 12                   #14 [hci0] 7.435915
      LE Read Remote Used Features (0x04)
        Status: Success (0x00)
        Handle: 64
        Features: 0x01 0x00 0x00 0x00 0x00 0x00 0x00 0x00
          LE Encryption
< ACL Data TX: Handle 64 flags 0x00 dlen 11                 #15 [hci0] 7.436010         # 发送配对请求
      SMP: Pairing Request (0x01) len 6
        IO capability: KeyboardDisplay (0x04)
        OOB data: Authentication data not present (0x00)
        Authentication requirement: Bonding, MITM, SC, No Keypresses (0x0d)
        Max encryption key size: 16
        Initiator key distribution: EncKey Sign (0x05)
        Responder key distribution: EncKey IdKey Sign (0x07)
< ACL Data TX: Handle 64 flags 0x00 dlen 7                  #16 [hci0] 7.441828         # 发送最大传输单元字节数
      ATT: Exchange MTU Request (0x02) len 2
        Client RX MTU: 517
> HCI Event: Number of Completed Packets (0x13) plen 5      #17 [hci0] 7.485108
        Num handles: 1
        Handle: 64
        Count: 2
> ACL Data RX: Handle 64 flags 0x02 dlen 11                 #18 [hci0] 7.533257         # 接收到设备发回来的配对信息
      SMP: Pairing Response (0x02) len 6
        IO capability: DisplayOnly (0x00)
        OOB data: Authentication data not present (0x00)
        Authentication requirement: Bonding, MITM, Legacy, No Keypresses (0x05)
        Max encryption key size: 16
        Initiator key distribution: EncKey Sign (0x05)
        Responder key distribution: EncKey IdKey Sign (0x07)
@ MGMT Event: User Passkey Request (0x0010) plen 7     {0x0003} [hci0] 7.533279
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
@ MGMT Event: User Passkey Request (0x0010) plen 7     {0x0002} [hci0] 7.533279
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
@ MGMT Event: User Passkey Request (0x0010) plen 7     {0x0001} [hci0] 7.533279
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
> ACL Data RX: Handle 64 flags 0x02 dlen 7                  #19 [hci0] 7.534164         # 设备最大接收传输单元字节数: 23
      ATT: Exchange MTU Response (0x03) len 2
        Server RX MTU: 23                                                               # #define L2CAP_MTU_SIZE                   23
< ACL Data TX: Handle 64 flags 0x00 dlen 11                 #20 [hci0] 7.534315         # 获取profile
      ATT: Read By Group Type Request (0x10) len 6
        Handle range: 0x0001-0xffff
        Attribute group type: Primary Service (0x2800)
> ACL Data RX: Handle 64 flags 0x02 dlen 24                 #21 [hci0] 7.728978         # 反馈profile
      ATT: Read By Group Type Response (0x11) len 19
        Attribute data length: 6
        Attribute group list: 3 entries
        Handle range: 0x0001-0x000b
        UUID: Generic Access Profile (0x1800)
        Handle range: 0x000c-0x000f
        UUID: Generic Attribute Profile (0x1801)
        Handle range: 0x0010-0x0022
        UUID: Device Information (0x180a)
< ACL Data TX: Handle 64 flags 0x00 dlen 11                 #22 [hci0] 7.729125         # 获取profile
      ATT: Read By Group Type Request (0x10) len 6
        Handle range: 0x0023-0xffff
        Attribute group type: Primary Service (0x2800)
> HCI Event: Number of Completed Packets (0x13) plen 5      #23 [hci0] 7.777342
        Num handles: 1
        Handle: 64
        Count: 2
> ACL Data RX: Handle 64 flags 0x02 dlen 18                 #24 [hci0] 7.874802         # 反馈profile
      ATT: Read By Group Type Response (0x11) len 13
        Attribute data length: 6
        Attribute group list: 2 entries
        Handle range: 0x0023-0x0033
        UUID: Unknown (0xfff0)
        Handle range: 0x0034-0xffff
        UUID: Unknown (0xffe0)
< ACL Data TX: Handle 64 flags 0x00 dlen 9                  #25 [hci0] 7.892517         # 发送Handle = 0x000f，0x0200
      ATT: Write Request (0x12) len 4
        Handle: 0x000f
          Data: 0200
> ACL Data RX: Handle 64 flags 0x02 dlen 5                  #26 [hci0] 7.972204
      ATT: Write Response (0x13) len 0
< ACL Data TX: Handle 64 flags 0x00 dlen 7                  #27 [hci0] 7.972370         # 读取Handle = 0x0003
      ATT: Read Request (0x0a) len 2
        Handle: 0x0003
> HCI Event: Number of Completed Packets (0x13) plen 5      #28 [hci0] 8.118772
        Num handles: 1
        Handle: 64
        Count: 2
> ACL Data RX: Handle 64 flags 0x02 dlen 26                 #29 [hci0] 8.119253         # Handle = 0x0003, 值：53696d706c6520424c45205065726970686572616c
      ATT: Read Response (0x0b) len 21
        Value: 53696d706c6520424c45205065726970686572616c                               # "Simple BLE Peripheral" --> GS_SetParameter( GGS_DEVICE_NAME_ATT, GAP_DEVICE_NAME_LEN, attDeviceName );
< ACL Data TX: Handle 64 flags 0x00 dlen 7                  #30 [hci0] 8.119390         # 读取Handle = 0x0005
      ATT: Read Request (0x0a) len 2
        Handle: 0x0005
> ACL Data RX: Handle 64 flags 0x02 dlen 7                  #31 [hci0] 8.264906
      ATT: Read Response (0x0b) len 2
        Value: 0000
< ACL Data TX: Handle 64 flags 0x00 dlen 7                  #32 [hci0] 8.265187         # 读取Handle = 0x0022
      ATT: Read Request (0x0a) len 2
        Handle: 0x0022
> HCI Event: Number of Completed Packets (0x13) plen 5      #33 [hci0] 8.313859
        Num handles: 1
        Handle: 64
        Count: 2
> ACL Data RX: Handle 64 flags 0x02 dlen 12                 #34 [hci0] 8.362495
      ATT: Read Response (0x0b) len 7
        Value: 010d0000001001
@ MGMT Command: User Passkey Reply (0x001e) plen 11   {0x0001} [hci0] 12.456286         # 自己输入的Passkey配对码
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Passkey: 0x0000
@ MGMT Event: Command Complete (0x0001) plen 10       {0x0001} [hci0] 12.456336
      User Passkey Reply (0x001e) plen 7
        Status: Success (0x00)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
< ACL Data TX: Handle 64 flags 0x00 dlen 21                #35 [hci0] 12.457159         # 发送配对确认信息
      SMP: Pairing Confirm (0x03) len 16
        Confim value: b88733ac9a1e113f15cdcad138fa40b1
> ACL Data RX: Handle 64 flags 0x02 dlen 21                #36 [hci0] 12.508516         # 接收配对确认信息
      SMP: Pairing Confirm (0x03) len 16
        Confim value: 83f4839b3893275092057a8d1b3a62a0
< ACL Data TX: Handle 64 flags 0x00 dlen 21                #37 [hci0] 12.508578         # 发送配对随机数
      SMP: Pairing Random (0x04) len 16
        Random value: 8f19c488461d074818d68af6ad25d9e8
> HCI Event: Number of Completed Packets (0x13) plen 5     #38 [hci0] 12.557429
        Num handles: 1
        Handle: 64
        Count: 2
> ACL Data RX: Handle 64 flags 0x02 dlen 21                #39 [hci0] 12.606069         # 接收配对随机数
      SMP: Pairing Random (0x04) len 16
        Random value: 02fc93c00eefa385a17b31b87c5488e2
< HCI Command: LE Start Encryption (0x08|0x0019) plen 28   #40 [hci0] 12.606150         # LE开始加密，生成相关参数
        Handle: 64
        Random number: 0x0000000000000000
        Encrypted diversifier: 0x0000
        Long term key: e3a02718a8a7c25f5935d88a4fcbc0c6
> HCI Event: Command Status (0x0f) plen 4                  #41 [hci0] 12.606615
      LE Start Encryption (0x08|0x0019) ncmd 1
        Status: Success (0x00)
> HCI Event: Encryption Change (0x08) plen 4               #42 [hci0] 12.898704         # 采用AES-CCM加密方式
        Status: Success (0x00)
        Handle: 64
        Encryption: Enabled with AES-CCM (0x01)
> ACL Data RX: Handle 64 flags 0x02 dlen 21                #43 [hci0] 12.996267         # 接收到加密信息
      SMP: Encryption Information (0x06) len 16
        Long term key: c2fdcc13bc559731dd2f395aef91460d
> ACL Data RX: Handle 64 flags 0x02 dlen 15                #44 [hci0] 13.044988
      SMP: Master Identification (0x07) len 10
        EDIV: 0xc4f0
        Rand: 0x9929ddda9d2a932c
> ACL Data RX: Handle 64 flags 0x02 dlen 21                #45 [hci0] 13.046111
      SMP: Identity Information (0x08) len 16
        Identity resolving key: bc53c7f11cd395c9bdace77216cb850c
> ACL Data RX: Handle 64 flags 0x02 dlen 12                #46 [hci0] 13.093753
      SMP: Identity Address Information (0x09) len 7
        Address type: Public (0x00)
        Address: 34:03:DE:16:24:27
> ACL Data RX: Handle 64 flags 0x02 dlen 21                #47 [hci0] 13.143058
      SMP: Signing Information (0x0a) len 16
        Signature key: bba4c7f28c1308e5d0c6299cba5dc7f1
@ MGMT Event: New Identity Resolv.. (0x0018) plen 30  {0x0003} [hci0] 13.143153
        Store hint: Yes (0x01)
        Random address: 00:00:00:00:00:00 (Non-Resolvable)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key: bc53c7f11cd395c9bdace77216cb850c
@ MGMT Event: New Identity Resolv.. (0x0018) plen 30  {0x0002} [hci0] 13.143153
        Store hint: Yes (0x01)
        Random address: 00:00:00:00:00:00 (Non-Resolvable)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key: bc53c7f11cd395c9bdace77216cb850c
@ MGMT Event: New Identity Resolv.. (0x0018) plen 30  {0x0001} [hci0] 13.143153
        Store hint: Yes (0x01)
        Random address: 00:00:00:00:00:00 (Non-Resolvable)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key: bc53c7f11cd395c9bdace77216cb850c
@ MGMT Event: New Signature Resol.. (0x0019) plen 25  {0x0003} [hci0] 13.143212
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated remote CSRK (0x03)
        Key: bba4c7f28c1308e5d0c6299cba5dc7f1
@ MGMT Event: New Signature Resol.. (0x0019) plen 25  {0x0002} [hci0] 13.143212
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated remote CSRK (0x03)
        Key: bba4c7f28c1308e5d0c6299cba5dc7f1
@ MGMT Event: New Signature Resol.. (0x0019) plen 25  {0x0001} [hci0] 13.143212
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated remote CSRK (0x03)
        Key: bba4c7f28c1308e5d0c6299cba5dc7f1
@ MGMT Event: New Signature Resol.. (0x0019) plen 25  {0x0003} [hci0] 13.143249
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated local CSRK (0x02)
        Key: 0ca568e5a19eba95ca2de95ee8c25947
@ MGMT Event: New Signature Resol.. (0x0019) plen 25  {0x0002} [hci0] 13.143249
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated local CSRK (0x02)
        Key: 0ca568e5a19eba95ca2de95ee8c25947
@ MGMT Event: New Signature Resol.. (0x0019) plen 25  {0x0001} [hci0] 13.143249
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated local CSRK (0x02)
        Key: 0ca568e5a19eba95ca2de95ee8c25947
@ MGMT Event: New Long Term Key (0x000a) plen 37      {0x0003} [hci0] 13.143293
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated legacy key (0x01)
        Master: 0x01
        Encryption size: 16
        Diversifier: f0c4
        Randomizer: 2c932a9ddadd2999
        Key: c2fdcc13bc559731dd2f395aef91460d
@ MGMT Event: New Long Term Key (0x000a) plen 37      {0x0002} [hci0] 13.143293
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated legacy key (0x01)
        Master: 0x01
        Encryption size: 16
        Diversifier: f0c4
        Randomizer: 2c932a9ddadd2999
        Key: c2fdcc13bc559731dd2f395aef91460d
@ MGMT Event: New Long Term Key (0x000a) plen 37      {0x0001} [hci0] 13.143293
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated legacy key (0x01)
        Master: 0x01
        Encryption size: 16
        Diversifier: f0c4
        Randomizer: 2c932a9ddadd2999
        Key: c2fdcc13bc559731dd2f395aef91460d
@ MGMT Event: New Long Term Key (0x000a) plen 37      {0x0003} [hci0] 13.143326
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated legacy key (0x01)
        Master: 0x00
        Encryption size: 16
        Diversifier: 8a21
        Randomizer: 5027ec1b2f853bfa
        Key: b91544569eb0f25450ab1fbb15cc3976
@ MGMT Event: New Long Term Key (0x000a) plen 37      {0x0002} [hci0] 13.143326
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated legacy key (0x01)
        Master: 0x00
        Encryption size: 16
        Diversifier: 8a21
        Randomizer: 5027ec1b2f853bfa
        Key: b91544569eb0f25450ab1fbb15cc3976
@ MGMT Event: New Long Term Key (0x000a) plen 37      {0x0001} [hci0] 13.143326
        Store hint: Yes (0x01)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
        Key type: Authenticated legacy key (0x01)
        Master: 0x00
        Encryption size: 16
        Diversifier: 8a21
        Randomizer: 5027ec1b2f853bfa
        Key: b91544569eb0f25450ab1fbb15cc3976
@ MGMT Event: Command Complete (0x0001) plen 10       {0x0001} [hci0] 13.143365
      Pair Device (0x0019) plen 7
        Status: Success (0x00)
        LE Address: 34:03:DE:16:24:27 (Texas Instruments)
< ACL Data TX: Handle 64 flags 0x00 dlen 21                #48 [hci0] 13.143400
      SMP: Encryption Information (0x06) len 16
        Long term key: b91544569eb0f25450ab1fbb15cc3976
< ACL Data TX: Handle 64 flags 0x00 dlen 15                #49 [hci0] 13.143418
      SMP: Master Identification (0x07) len 10
        EDIV: 0x218a
        Rand: 0xfa3b852f1bec2750
< ACL Data TX: Handle 64 flags 0x00 dlen 21                #50 [hci0] 13.143428
      SMP: Signing Information (0x0a) len 16
        Signature key: 0ca568e5a19eba95ca2de95ee8c25947
> HCI Event: Number of Completed Packets (0x13) plen 5     #51 [hci0] 13.191977
        Num handles: 1
        Handle: 64
        Count: 2
> HCI Event: Number of Completed Packets (0x13) plen 5     #52 [hci0] 13.406822
        Num handles: 1
        Handle: 64
        Count: 1
> ACL Data RX: Handle 64 flags 0x02 dlen 16                #53 [hci0] 13.435221
      LE L2CAP: Connection Parameter Update Request (0x12) ident 2 len 8
        Min interval: 80
        Max interval: 800
        Slave latency: 0
        Timeout multiplier: 1000
@ MGMT Event: New Connection Para.. (0x001c) plen 16  {0x0003} [hci0] 13.435278
        Store hint: Reserved (0x27)
        LE Address: 01:34:03:DE:16:24 (OUI 01-34-03)
        Min connection interval: 80
        Max connection interval: 800
        Connection latency: 0 (0x0000)
        Supervision timeout: 1000
@ MGMT Event: New Connection Para.. (0x001c) plen 16  {0x0002} [hci0] 13.435278
        Store hint: Reserved (0x27)
        LE Address: 01:34:03:DE:16:24 (OUI 01-34-03)
        Min connection interval: 80
        Max connection interval: 800
        Connection latency: 0 (0x0000)
        Supervision timeout: 1000
@ MGMT Event: New Connection Para.. (0x001c) plen 16  {0x0001} [hci0] 13.435278
        Store hint: Reserved (0x27)
        LE Address: 01:34:03:DE:16:24 (OUI 01-34-03)
        Min connection interval: 80
        Max connection interval: 800
        Connection latency: 0 (0x0000)
        Supervision timeout: 1000
< ACL Data TX: Handle 64 flags 0x00 dlen 10                #54 [hci0] 13.435339
      LE L2CAP: Connection Parameter Update Response (0x13) ident 2 len 2
        Result: Connection Parameters accepted (0x0000)
< HCI Command: LE Connection Update (0x08|0x0013) plen 14  #55 [hci0] 13.435363
        Handle: 64
        Min connection interval: 100.00 msec (0x0050)
        Max connection interval: 1000.00 msec (0x0320)
        Connection latency: 0 (0x0000)
        Supervision timeout: 10000 msec (0x03e8)
        Min connection length: 0.000 msec (0x0000)
        Max connection length: 0.000 msec (0x0000)
> HCI Event: Command Status (0x0f) plen 4                  #56 [hci0] 13.435892
      LE Connection Update (0x08|0x0013) ncmd 1
        Status:
```