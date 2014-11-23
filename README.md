arduinoyun_temp
===============

Check the temperature and humidity in any room. 

# Arduino YUN to give the temperature in any room.
A little application that used a DHT22 temperature sensor attached to a Arduino YUN using a combination of the bridge librarary and node.js application.

The node.js part is not really nessesary but I had two reason to add node.js
* I'm in the process of learning node.js
* as I started to write arduino code it was a lot of string manipulation to make the web pages.
* why reimplement something that's working. I did look into using bridge with node directly, but didn't like how the solution turned out. But check out this - http://www.tigoe.com/pcomp/code/arduinowiring/1216/ 

So I deceided to add node.js so that the arduino sketch become as simple as possiblre and then adding the website 
parts with node.js.

The sketch is based on the bridge exmaple: http://arduino.cc/en/Tutorial/Bridge

## Parts
* Arduino YUN - http://arduino.cc/en/Main/ArduinoBoardYun?from=Products.ArduinoYUN
* A DHT22 sensor - http://www.adafruit.com/products/393

## How
### Add expand YUN's diskspace 
I followed these instructions to expand the diskspace of the Linux micro processor - http://arduino.cc/en/Tutorial/ExpandingYunDiskSpace
If you don't do that you will probably run in to problems when installing node.js, I did and had to flash the arduino YUN
since it was in a un-usable state after I installe node.js forst time.

### Install node.js 
Followd these instructions to install node.js in the Linux microprocessor of the YUN - http://blog.arduino.cc/2014/07/07/node-js-on-the-arduino-yun/

ssh to the arduino `ssh root@arduino.local` and creare a folder called node:  `mkdir /mnt/sd/arduino/node'

### Connect the DHT22
Follow these instructions on how to connect the DHT22 to the Arduino - https://www.virtuabotix.com/virtuabotix-dht22-pinout-coding-guide/

### Upload the sketch
Download the DHT22_1S0A Library from here - https://www.virtuabotix.com/?attachment_id=1854, download link - https://virtuabotix-virtuabotixllc.netdna-ssl.com/core/wp-content/uploads/2012/09/DHT22_1S0A.zip

Add the library the DHT22_1S0A to your Arduino editor by adding the library (_Sketch/Import Library/Add Library_).
Connect the Arduino YUN to your computer using the USB and start the arduino edior, load the sketch, `temerature_server.ino` 
from the arduino folder of this repo and upload.

You can test if this step worked by poiting the a browser to - http://arduino.local/arduino/tempF - and you should see
the temerature.

### Upload the node app
In the root of this repo do the npm install

* `npm install`
* Zip up the code, including node_modules
`tar czf temperature.tar.gz temperatur` from the command line when you are one level up from this repo. 
* scp the `temperature.tar.gz` file to arduino - `scp temperatur.tar.gz root@arduino.local:/mnt/sd/arduino/node/.`
* Unzip the file - temperature.tar.gz 
  1. `ssh root@arduino.local`
  2. `cd /mnt/sda1/arduino/node/`
  3. `tar -xzvf temperature.tar.gz`
  

### Run the node app
ssh to the arduino box `ssh root@arduino.local` and start the node server 
`node server.js` and you should see `Express started on http://localhost:3000; press Ctrl-C to terminate.`

### Check the temperature
Navigate to http://arduino.local:3000/temperature and you should see the temperature and humidity. It's takes a few 
secounds before the page loads. 


