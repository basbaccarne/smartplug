# smartplug
This project connects a smart plug (Tapo P100) to an Arduino to control a ventilation system triggered by the light in the toilet.
## Components
- [Tapo P100](https://www.tp-link.com/nl-be/home-networking/smart-plug/tapo-p100/)
- [xiao esp32s3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html)
- [3.7V lithium battery](https://www.kiwi-electronics.com/nl/lithium-polymer-li-po-accu-3-7v-500mah-2200): [documentation](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/)
- LDR light dependent resistor 
<p align="center">
<img src="/img/hardware.jpg" alt="components" style="height: 7cm; width:10cm;"/>
</p>

## Platforms & software
- Connect P100 with the tapo app
- Configure a shortcut program in the tapo app (e.g. set the plug on for 5 seconds)
- Connect the tapo app to [IFTTT](ifttt.com)
- Create an IFTTT applet with input: webook (on eventname "flush") and output: tapo (shortcut)
- Test using the test module in the [IFTTT webhook documentation](https://ifttt.com/maker_webhooks) (enter the event name, e.g. "flush" in the web request)

<p align="center">
<img src="/img/ifttt.png" alt="ifttt applet" style="height: 6cm; width:10cm;"/>
</p>

## Set-up Arduino to send a webhook to IFTTT
- WiFi connection is managed by "WiFi.h" (& requires an extra physical antenna on the esp32s) ([test](tests/1_WiFi/1_WiFi.ino))
- Webhooks are managed by "HTTPClient.h" ([test](tests/2_WiFi_Webhook/2_WiFi_Webhook.ino))

<p align="center">
<img src="https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32S3/img/5.gif" alt="antenna" style="height: 6cm; width:10cm;"/>
</p>

## Set-up Arduino to trigger on light detection
- LDR and thresholds & LED feedback - [test without sending the webhook](tests/3_LDR/3_LDR.ino)
- Integrated script that reads the LDR sensor, detects when the light is turned off, connects the esp32s3 to WiFi & sends a webhook to IFTTT when the light is turned off- [test](tests/4_integration/4_integration.ino)

<p align="center">
<img src="img/wires.png" alt="wires" style="height: 8cm; width:10cm;"/>

</p>
<p align="center">
    <img src="img/threshold.gif" alt="interaction" style="height: 6cm; width:10cm;"/>
</p>

## Set-up Arduino power management
- [ ] Sleep

## Casing
- [ ] CAD file

## History & alternative plans
- [Hacking the inside of the Tapo](https://www.youtube.com/watch?v=99iAK1JeAeo) > hard to pry open (& less safe)
- Linking with [Samsung SmartThings](https://smartthings.developer.samsung.com/) & create an Automation triggered by a webhook or MQTT > too complex
- Linking with Google Assistant and set-up an [Assistant Relay](https://greghesp.github.io/assistant-relay/docs/introduction) server > Backup plan
