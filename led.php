<?php
    error_log("start back script!\n", 3, "run.log");

    error_log($_SERVER['REQUEST_TIME']. ": " . $_GET["setValue"] . "\n", 3, "run.log");

    # $ledFile = fopen("ledFile.txt", "w");
    $ledFile = fopen("/sys/class/gpio/gpio10/value", "w");
    if ($_GET["setValue"] == "Led On") {
        fwrite($ledFile, "0\n");
    } else if ($_GET["setValue"] == "Led Off") {
        fwrite($ledFile, "1\n");
    }
    fclose($ledFile);

    echo "success";
    error_log("over back script!\n", 3, "run.log");
?>
