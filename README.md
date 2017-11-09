# XBeeWifiBasic

* API mode = 2 (enable with escape)
* Serial baudrate must match with Arduino
* UDP connection
* Wifi association should be done with X-CTU

## function

* xbeesend
	* send String at dest IP and dest Port
* xbeereceive
	* parse received packet and return string
	* src IP, src Port, and other information are parsed internally.

## memo

* ボーレートが高すぎると追いつかないことがある（特にreceiveの時)
	* sendは115200までパケット落ちなく使用できる
	* receiveは57600は確認した

