# smartplug
In this project, I want to connect a smart plug (Tapo P100) to an Arduino to control a ventilation system triggered by the light in the toilet.
## Components
- Tapo P100
- xiao esp32s3
- 3.7V lithium battery: [documentation](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/)
- LDR light dependent resistor 
## Platforms & software
- Connect P100 with the tapo app
- Configure a shortcut program in the tapo app (e.g. set the plug on for 5 seconds)
- Connect the tapo app to [IFTTT](ifttt.com)
- Create an IFTTT applet with input: webook (on eventname "flush") and output: tapo (shortcut)
- Test using the test module in the [IFTTT webhook documentation](https://ifttt.com/maker_webhooks) (enter the event name, e.g. "flush" in the web request)

## Setting up the Arduino to send a webhook to IFTTT when the light is turned off
- WiFi connection is managed by "WiFi.h" (& requires an extra physical antenna on the esp32s) ([test 1](/tests/1_WiFi.ino))
- Webhooks are managed by "HTTPClient.h" ([test 2](/tests/2_WiFi _Webhook.ino))
 
## History & alternative plans
- [Hacking the inside of the Tapo](https://www.youtube.com/watch?v=99iAK1JeAeo) > hard to pry open (& less safe)
- Linking with [Samsung SmartThings](https://smartthings.developer.samsung.com/) & create an Automation triggered by a webhook or MQTT > too complex
- Linking with Google Assistant and set-up an [Assistant Relay](https://greghesp.github.io/assistant-relay/docs/introduction) server > Backup plan
