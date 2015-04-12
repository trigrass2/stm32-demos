file-io-benchmark
=================

SD card disk IO benchmark.

prints out the performance of a bunch of file IO operations.

boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P
 - Any stm32f1 or stm32f4 board with SDIO and a console USART support would work.


test
----

 - run a serial-terminal program to monitor the board console output.

 
``` bash
	
	# assumes you have pyserial installed, and that you use a USB serial port cable
	miniterm.py -p /dev/ttyUSB0 -b 115200

```

8GB sandisk class 4, BOARD=uemb4, USE_THREAD_AWARE_SDCARD_DRIVER=0:

write	1 blocks of 1 bytes (0kB), 3 cycles. tmax=0.1351s, tav=0.0477s,tmin=0.004s, rate=0.02kBps
write	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.004s,tmin=0.004s, rate=24.414kBps
write	1000 blocks of 1 bytes (1kB), 3 cycles. tmax=0.0122s, tav=0.0122s,tmin=0.0122s, rate=81.38kBps
write	1000000 blocks of 1 bytes (1000kB), 3 cycles. tmax=16.2652s, tav=15.6125s,tmin=14.3114s, rate=64.05kBps
write	1 blocks of 10 bytes (0.01kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=7.324kBps
write	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.0081s, tav=0.0068s,tmin=0.004s, rate=146.484kBps
write	1000 blocks of 10 bytes (10kB), 3 cycles. tmax=0.0942s, tav=0.0846s,tmin=0.0778s, rate=118.132kBps
write	1000000 blocks of 10 bytes (10000kB), 3 cycles. tmax=92.1518s, tav=91.1223s,tmin=89.3501s, rate=109.742kBps
write	1 blocks of 100 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
write	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.0983s, tav=0.0983s,tmin=0.0983s, rate=101.725kBps
write	1000 blocks of 100 bytes (100kB), 3 cycles. tmax=2.519s, tav=1.4049s,tmin=0.8355s, rate=71.178kBps
write	1 blocks of 1000 bytes (1kB), 3 cycles. tmax=0.0081s, tav=0.0068s,tmin=0.004s, rate=146.484kBps
write	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=0.8683s, tav=0.856s,tmin=0.8478s, rate=116.813kBps
write	1000 blocks of 1000 bytes (1000kB), 1 cycles. tmax=10.2154s, tav=10.2154s,tmin=10.2154s, rate=97.891kBps
write	1 blocks of 1024 bytes (1.024kB), 3 cycles. tmax=0.0081s, tav=0.0081s,tmin=0.0081s, rate=124.999kBps
write	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.4751s, tav=0.4478s,tmin=0.4218s, rate=228.658kBps
write	1000 blocks of 1024 bytes (1024kB), 1 cycles. tmax=5.8654s, tav=5.8654s,tmin=5.8654s, rate=174.581kBps
write	1 blocks of 4096 bytes (4.096kB), 3 cycles. tmax=0.0081s, tav=0.0068s,tmin=0.004s, rate=600kBps
write	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=0.6389s, tav=0.6171s,tmin=0.5816s, rate=663.716kBps
write	1000 blocks of 4096 bytes (4096kB), 1 cycles. tmax=6.7747s, tav=6.7747s,tmin=6.7747s, rate=604.594kBps
write	1000 blocks of 8192 bytes (8192kB), 1 cycles. tmax=11.5834s, tav=11.5834s,tmin=11.5834s, rate=707.213kBps
read	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
read	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.004s, tav=0.004s,tmin=0.004s, rate=244.14kBps
read	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.0409s, tav=0.0382s,tmin=0.0368s, rate=261.579kBps
read	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=0.2662s, tav=0.2662s,tmin=0.2662s, rate=375.6kBps
read	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.1925s, tav=0.1925s,tmin=0.1925s, rate=531.914kBps
read	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=0.2088s, tav=0.2075s,tmin=0.2047s, rate=1973.684kBps
read	100 blocks of 32768 bytes (3276.8kB), 3 cycles. tmax=1.6424s, tav=1.6411s,tmin=1.6383s, rate=1996.672kBps


8GB sandisk class 4, BOARD=uemb4, USE_THREAD_AWARE_SDCARD_DRIVER=1:

write	1 blocks of 1 bytes (0kB), 3 cycles. tmax=0.0081s, tav=0.0027s,tmin=0s, rate=0.366kBps
write	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
write	1000 blocks of 1 bytes (1kB), 3 cycles. tmax=0.0122s, tav=0.0122s,tmin=0.0122s, rate=81.38kBps
write	1000000 blocks of 1 bytes (1000kB), 3 cycles. tmax=16.2856s, tav=16.2283s,tmin=16.1587s, rate=61.62kBps
write	1 blocks of 10 bytes (0.01kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=7.324kBps
write	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.0081s, tav=0.0081s,tmin=0.0081s, rate=122.07kBps
write	1000 blocks of 10 bytes (10kB), 3 cycles. tmax=0.1064s, tav=0.0887s,tmin=0.0778s, rate=112.68kBps
write	1000000 blocks of 10 bytes (10000kB), 3 cycles. tmax=89.2723s, tav=88.8367s,tmin=88.3179s, rate=112.565kBps
write	1 blocks of 100 bytes (0.1kB), 3 cycles. tmax=0s, tav=0s,tmin=0s, rate=infkBps
write	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.1023s, tav=0.086s,tmin=0.0778s, rate=116.257kBps
write	1000 blocks of 100 bytes (100kB), 3 cycles. tmax=0.8765s, tav=0.8506s,tmin=0.8355s, rate=117.563kBps
write	1 blocks of 1000 bytes (1kB), 3 cycles. tmax=0.0081s, tav=0.0068s,tmin=0.004s, rate=146.484kBps
write	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=0.8806s, tav=0.8669s,tmin=0.8437s, rate=115.342kBps
write	1000 blocks of 1000 bytes (1000kB), 1 cycles. tmax=10.2113s, tav=10.2113s,tmin=10.2113s, rate=97.93kBps
write	1 blocks of 1024 bytes (1.024kB), 3 cycles. tmax=0.0081s, tav=0.0068s,tmin=0.004s, rate=150kBps
write	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.4833s, tav=0.456s,tmin=0.4382s, rate=224.55kBps
write	1000 blocks of 1024 bytes (1024kB), 1 cycles. tmax=6.5372s, tav=6.5372s,tmin=6.5372s, rate=156.641kBps
write	1 blocks of 4096 bytes (4.096kB), 3 cycles. tmax=0.0081s, tav=0.0054s,tmin=0.004s, rate=750kBps
write	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=0.6348s, tav=0.6266s,tmin=0.6144s, rate=653.594kBps
write	1000 blocks of 4096 bytes (4096kB), 1 cycles. tmax=6.6928s, tav=6.6928s,tmin=6.6928s, rate=611.995kBps
write	1000 blocks of 8192 bytes (8192kB), 1 cycles. tmax=12.6894s, tav=12.6894s,tmin=12.6894s, rate=645.577kBps
read	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
read	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.004s, tav=0.0027s,tmin=0s, rate=366.21kBps
read	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.0245s, tav=0.0232s,tmin=0.0204s, rate=430.836kBps
read	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=0.1966s, tav=0.1952s,tmin=0.1925s, rate=512.183kBps
read	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.1597s, tav=0.1583s,tmin=0.1556s, rate=646.551kBps
read	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=0.172s, tav=0.172s,tmin=0.172s, rate=2380.952kBps
read	100 blocks of 32768 bytes (3276.8kB), 3 cycles. tmax=1.3762s, tav=1.3748s,tmin=1.3721s, rate=2383.316kBps

1GB transcend class ??, BOARD=uemb4, USE_THREAD_AWARE_SDCARD_DRIVER=1:

write	1 blocks of 1 bytes (0kB), 3 cycles. tmax=0s, tav=0s,tmin=0s, rate=infkBps
write	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0s, tav=0s,tmin=0s, rate=infkBps
write	1000 blocks of 1 bytes (1kB), 3 cycles. tmax=0.1556s, tav=0.1542s,tmin=0.1515s, rate=6.481kBps
write	1000000 blocks of 1 bytes (1000kB), 3 cycles. tmax=20.1891s, tav=20.1263s,tmin=20.0908s, rate=49.686kBps
write	1 blocks of 10 bytes (0.01kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=7.324kBps
write	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.1515s, tav=0.1515s,tmin=0.1515s, rate=6.598kBps
write	1000 blocks of 10 bytes (10kB), 3 cycles. tmax=0.2744s, tav=0.2717s,tmin=0.2703s, rate=36.805kBps
write	1000000 blocks of 10 bytes (10000kB), 3 cycles. tmax=152.2524s, tav=152.1158s,tmin=152.0476s, rate=65.739kBps
write	1 blocks of 100 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
write	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.258s, tav=0.258s,tmin=0.258s, rate=38.752kBps
write	1000 blocks of 100 bytes (100kB), 3 cycles. tmax=1.4172s, tav=1.3994s,tmin=1.3844s, rate=71.455kBps
write	1 blocks of 1000 bytes (1kB), 3 cycles. tmax=0.1474s, tav=0.1474s,tmin=0.1474s, rate=6.781kBps
write	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=1.409s, tav=1.3858s,tmin=1.3721s, rate=72.159kBps
write	1000 blocks of 1000 bytes (1000kB), 1 cycles. tmax=14.68s, tav=14.68s,tmin=14.68s, rate=68.119kBps
write	1 blocks of 1024 bytes (1.024kB), 3 cycles. tmax=0.1556s, tav=0.1556s,tmin=0.1556s, rate=6.578kBps
write	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.9011s, tav=0.8738s,tmin=0.856s, rate=117.187kBps
write	1000 blocks of 1024 bytes (1024kB), 1 cycles. tmax=9.5191s, tav=9.5191s,tmin=9.5191s, rate=107.573kBps
write	1 blocks of 4096 bytes (4.096kB), 3 cycles. tmax=0.1474s, tav=0.1474s,tmin=0.1474s, rate=27.777kBps
write	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=1.1509s, tav=1.1468s,tmin=1.1427s, rate=357.142kBps
write	1000 blocks of 4096 bytes (4096kB), 1 cycles. tmax=11.0059s, tav=11.0059s,tmin=11.0059s, rate=372.162kBps
write	1000 blocks of 8192 bytes (8192kB), 1 cycles. tmax=22.0979s, tav=22.0979s,tmin=22.0979s, rate=370.713kBps
read	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
read	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=732.421kBps
read	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.0122s, tav=0.0122s,tmin=0.0122s, rate=813.802kBps
read	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=0.1064s, tav=0.1064s,tmin=0.1064s, rate=939.002kBps
read	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.0655s, tav=0.0628s,tmin=0.0614s, rate=1630.434kBps
read	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=0.1064s, tav=0.1064s,tmin=0.1064s, rate=3846.153kBps
read	100 blocks of 32768 bytes (3276.8kB), 3 cycles. tmax=0.856s, tav=0.856s,tmin=0.856s, rate=3827.75kBps

32GB strontium class 10, BOARD=uemb4, USE_THREAD_AWARE_SDCARD_DRIVER=1:

write	1 blocks of 1 bytes (0kB), 3 cycles. tmax=0s, tav=0s,tmin=0s, rate=infkBps
write	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
write	1000 blocks of 1 bytes (1kB), 3 cycles. tmax=0.0081s, tav=0.0081s,tmin=0.0081s, rate=122.07kBps
write	1000000 blocks of 1 bytes (1000kB), 3 cycles. tmax=11.436s, tav=10.8844s,tmin=10.0433s, rate=91.874kBps
write	1 blocks of 10 bytes (0.01kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=7.324kBps
write	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.004s, tav=0.004s,tmin=0.004s, rate=244.14kBps
write	1000 blocks of 10 bytes (10kB), 3 cycles. tmax=0.0655s, tav=0.0655s,tmin=0.0655s, rate=152.587kBps
write	1000000 blocks of 10 bytes (10000kB), 3 cycles. tmax=43.4749s, tav=42.1778s,tmin=41.5129s, rate=237.091kBps
write	1 blocks of 100 bytes (0.1kB), 3 cycles. tmax=0s, tav=0s,tmin=0s, rate=infkBps
write	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.0532s, tav=0.0477s,tmin=0.0368s, rate=209.263kBps
write	1000 blocks of 100 bytes (100kB), 3 cycles. tmax=0.5488s, tav=0.5092s,tmin=0.43s, rate=196.359kBps
write	1 blocks of 1000 bytes (1kB), 3 cycles. tmax=0.004s, tav=0.004s,tmin=0.004s, rate=244.14kBps
write	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=0.9625s, tav=0.6813s,tmin=0.5324s, rate=146.777kBps
write	1000 blocks of 1000 bytes (1000kB), 1 cycles. tmax=4.2926s, tav=4.2926s,tmin=4.2926s, rate=232.958kBps
write	1 blocks of 1024 bytes (1.024kB), 3 cycles. tmax=0.3686s, tav=0.1256s,tmin=0.004s, rate=8.152kBps
write	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.3031s, tav=0.2976s,tmin=0.2908s, rate=344.036kBps
write	1000 blocks of 1024 bytes (1024kB), 1 cycles. tmax=3.3054s, tav=3.3054s,tmin=3.3054s, rate=309.789kBps
write	1 blocks of 4096 bytes (4.096kB), 3 cycles. tmax=0.004s, tav=0.0027s,tmin=0s, rate=1500kBps
write	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=0.3194s, tav=0.3153s,tmin=0.3072s, rate=1298.701kBps
write	1000 blocks of 4096 bytes (4096kB), 1 cycles. tmax=3.4037s, tav=3.4037s,tmin=3.4037s, rate=1203.369kBps
write	1000 blocks of 8192 bytes (8192kB), 1 cycles. tmax=3.7109s, tav=3.7109s,tmin=3.7109s, rate=2207.505kBps
read	100 blocks of 1 bytes (0.1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=73.242kBps
read	100 blocks of 10 bytes (1kB), 3 cycles. tmax=0.004s, tav=0.0013s,tmin=0s, rate=732.421kBps
read	100 blocks of 100 bytes (10kB), 3 cycles. tmax=0.0081s, tav=0.0081s,tmin=0.0081s, rate=1220.703kBps
read	100 blocks of 1000 bytes (100kB), 3 cycles. tmax=0.0696s, tav=0.0669s,tmin=0.0655s, rate=1494.738kBps
read	100 blocks of 1024 bytes (102.4kB), 3 cycles. tmax=0.045s, tav=0.045s,tmin=0.045s, rate=2272.727kBps
read	100 blocks of 4096 bytes (409.6kB), 3 cycles. tmax=0.0901s, tav=0.0901s,tmin=0.0901s, rate=4545.454kBps
read	100 blocks of 32768 bytes (3276.8kB), 3 cycles. tmax=0.4587s, tav=0.4587s,tmin=0.4587s, rate=7142.856kBps

