<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>Low Level Logic Of IoT</title>
    <script type="text/javascript">

        window.onload=function(){
            console.log("onload");

            window.WebSocket = window.WebSocket || window.MozWebSocket;
            var websocket = new WebSocket('ws://192.168.137.2:5678');
            websocket.onopen = function () {
                websocket.send("start");
            };
            websocket.onerror = function () {
                console.log("ws connect error");
            };
            websocket.onmessage = function (message) {
                if (message.data.length > 0) {
                    console.log(message.data);

                    if (message.data == "0") 
                        document.body.style.backgroundColor = "white";
                    else if(message.data == "1")
                        document.body.style.backgroundColor = "green";
                }
            };
        }

        function setValue() {
            var setValue = document.getElementById('setValue');

            console.log(setValue);

            var request = new XMLHttpRequest();
            request.open('GET', "led.php?setValue=" + setValue.value);
            request.onreadystatechange = function(){
                if(request.readyState === 4 && request.status === 200){
                    if (setValue.value == "Led On")
                        setValue.value = "Led Off";
                    else
                        setValue.value = "Led On";

                    console.log(request);
                }

            };
            request.send(null);
        }
    </script>
  </head>

  <body>
    <div>
      <input id="setValue" type="button" onclick="setValue()" value="Led On" />
    </div>

    <div style="margin-top: 60px;">
      <img src="http://192.168.137.2:8008?action=stream">
    </div>
  </body>
</html>
