#include <Ethernet_Generic.h>

#include "../buzzer/buzzer.h"
#include "../config.h"
#include "../models/ScanData.h"
#include "../models/HttpResponse.h"
#include "../jsonSerializer/jsonSerializer.h"
#include "../led/led.h"

IPAddress server;
byte mac[] = MAC_ADDRESS;

class HTTPClient
{
public:
	HTTPClient(EthernetClient &client, IPAddress server, uint16_t port)
			: client(client), server(server), port(port) {}

	HttpResponse fetch(const String &endpoint, const String &json)
	{
		HttpResponse response;
		response.success = false;
		response.statusCode = 0;
		response.body = "";

		if (!client.connect(server, port))
		{
			return response;
		}

		sendHttpRequest(endpoint, json);

		String rawResponse = readHttpResponse();

		client.stop();

		response.statusCode = extractStatusCode(rawResponse);
		response.body = extractResponseBody(rawResponse);
		response.success = response.statusCode >= 200 && response.statusCode < 300;

		return response;
	}

private:
	EthernetClient &client;
	IPAddress server;
	uint16_t port;

	void sendHttpRequest(const String &endpoint, const String &json)
	{
		client.print("POST ");
		client.print(endpoint);
		client.println(" HTTP/1.1");

		client.print("Host: ");
		client.println(SERVER_HOST);
		client.println("Content-Type: application/json");
		client.print("Content-Length: ");
		client.println(json.length());
		client.println("Connection: close");
		client.println();

		client.println(json);
	}

	String readHttpResponse()
	{
		unsigned long timeout = millis();

		String response;
		response.reserve(512);
		while (millis() - timeout < 3000)
		{
			while (client.available())
			{
				response += (char)client.read();
				timeout = millis();
			}

			if (!client.connected() && !client.available())
				break;
		}

		return response;
	}

	String extractResponseBody(const String &response)
	{
		int headerEnd = response.indexOf("\r\n\r\n");

		if (headerEnd == -1)
			return "";

		return response.substring(headerEnd + 4);
	}

	int extractStatusCode(const String &response)
	{
		int firstSpace = response.indexOf(' ');
		if (firstSpace == -1)
			return 0;

		int secondSpace = response.indexOf(' ', firstSpace + 1);
		if (secondSpace == -1)
			return 0;

		return response.substring(firstSpace + 1, secondSpace).toInt();
	}
};

void ethernetInit()
{
	pinMode(W5500_CS, OUTPUT);
	pinMode(W5500_RST, OUTPUT);

	digitalWrite(W5500_CS, HIGH);
	digitalWrite(W5500_RST, LOW);
	delay(10);
	digitalWrite(W5500_RST, HIGH);
	delay(200);

	Ethernet.init(W5500_CS);
	Ethernet.begin(mac, 15000, 4000);

	server.fromString(SERVER_HOST);

	digitalWrite(W5500_CS, HIGH);
}

void ethernetMaintain(unsigned long runtime)
{
	if (Ethernet.localIP() == IPAddress(0, 0, 0, 0))
	{
		unsigned long elapsed = millis() - runtime;
		LOG("IP lost — reinitializing...");
		int result = Ethernet.begin(mac, 15000, 4000);
		String time = "<" + String(elapsed) + "> - maintain, IP: ";
		LOGF(time, Ethernet.localIP());
	}
}

void sendRequest(const ScanData &scanData)
{
	String json = serializeToJson(scanData);

	EthernetClient ethernetClient;
	HTTPClient httpClient(ethernetClient, server, SERVER_PORT);
	HttpResponse response = httpClient.fetch(SCAN_ENDPOINT, json);

	switch (response.statusCode)
	{
	case 201:
		ledGreenOn();
		ledYellowOn();
		beepTagAdded();
		break;
	case 202:
		ledGreenOn();
		ledYellowOn();
		beepAdmin();
		break;
	case 204:
		ledGreenOn();
		beepAccepted();
		break;
	case 403:
		ledRedOn();
		beepUnassigned();
		break;
	case 404:
		ledRedOn();
		beepUnregistered();
		break;
	case 409:
		ledYellowOn();
		ledRedOn();
		beepConflict();
		break;
	default:
		ledRedOn();
		beepError();
		break;
	}
}
