/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5AtomS3 sample source code
*                          配套  M5AtomS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/AtomS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/AtomS3
*
* Describe: WIFI TCP.
* Date: 2023/1/15
*******************************************************************************
  M5AtomS3 will sends a message to a TCP server
  M5AtomS3 将向TCP服务器发送一条数据
*/

#include <M5AtomS3.h>
#include <WiFi.h>
#include <WiFiMulti.h>

// Set the name and password of the wifi to be connected.
// 配置所连接wifi的名称和密码
const char* ssid     = "your-ap";
const char* password = "your-password";
WiFiMulti WiFiMulti;

void setup() {
    int sum = 0;
    AtomS3.begin();  // Init M5AtomS3.  初始化M5AtomS3
    WiFiMulti.addAP(
        ssid,
        password);  // Add wifi configuration information.  添加wifi配置信息
    AtomS3.Lcd.printf(
        "Waiting connect to WiFi: %s ...",
        ssid);  // Serial port output format string.  串口输出格式化字符串
    while (WiFiMulti.run() !=
           WL_CONNECTED) {  // If the connection to wifi is not established
                            // successfully.  如果没有与wifi成功建立连接
        AtomS3.Lcd.print(".");
        delay(1000);
        sum += 1;
        if (sum == 8) AtomS3.Lcd.print("Conncet failed!");
    }
    AtomS3.Lcd.println("\nWiFi connected");
    AtomS3.Lcd.print("IP address: ");
    AtomS3.Lcd.println(
        WiFi.localIP());  // The serial port outputs the IP address
                          // of the M5AtomS3.  串口输出M5AtomS3的IP地址
    delay(500);
}

void loop() {
    AtomS3.Lcd.setCursor(0, 40);
    const char* host = "www.baidu.com";  // Set the IP address or DNS of the TCP
                                         // server.  设置TCP服务器的ip或dns
    const uint16_t port =
        80;  // The port of the TCP server is specified.  设置TCP服务器的端口
    AtomS3.Lcd.printf("Connecting to: %s\n", host);

    WiFiClient client;
    if (!client.connect(
            host,
            port)) {  // Connect to the server. 0 is returned if the
                      // connection fails. 连接服务器,若连接失败返回0
        AtomS3.Lcd.print(
            "Connection failed.\nWaiting 5 seconds before retrying...\n");
        delay(5000);
        return;
    }
    // send an arbitrary string to the server.  发送一个字符串到上边连接的服务器
    client.print("Send this data to the server");
    // send a basic document request to the server.
    // 向服务器发送一个基本的文档请求.
    client.print("GET /index.html HTTP/1.1\n\n");
    int maxloops = 0;

    // wait for the server's reply to become available
    // 等待服务器的回复
    while (!client.available() && maxloops < 1000) {
        maxloops++;
        delay(1);  // delay 1 msec
    }
    if (client.available() >
        0) {  // Detects whether data is received.  检测是否接收到数据
        String line = client.readStringUntil(
            '\r');  // Read information from data received by the device until
                    // \r is read.  从设备接收到的数据中读取信息,直至读取到\r时
        AtomS3.Lcd.println(line);  // String received by serial port output.
                                   // 串口输出接收到的字符串
    } else {
        AtomS3.Lcd.println("client.available() timed out ");
    }
    AtomS3.Lcd.println("Closing connection.");
    client.stop();
    AtomS3.Lcd.println("Waiting 5 seconds before restarting...");
    delay(5000);
    AtomS3.Lcd.fillRect(0, 40, 320, 220, BLACK);
}
