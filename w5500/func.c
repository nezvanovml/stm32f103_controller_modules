#if W5500Connection == 1 // relay, ventilation, lights, access, sensors, watering, leaks
#define W5500_resetPort GPIOA
#define W5500_resetPin GPIO_Pin_3

#define W5500_csPort GPIOA
#define W5500_csPin GPIO_Pin_4

#define W5500_MISOPort GPIOA
#define W5500_MISOPin GPIO_Pin_6

#define W5500_MOSIPort GPIOA
#define W5500_MOSIPin GPIO_Pin_7

#define W5500_clockPort GPIOA
#define W5500_clockPin GPIO_Pin_5

#define W5500_SPI 1
#elif W5500Connection == 2 // FSCD, movesensors
#define W5500_resetPort GPIOA
#define W5500_resetPin GPIO_Pin_8

#define W5500_csPort GPIOB
#define W5500_csPin GPIO_Pin_12

#define W5500_MISOPort GPIOB
#define W5500_MISOPin GPIO_Pin_14

#define W5500_MOSIPort GPIOB
#define W5500_MOSIPin GPIO_Pin_15

#define W5500_clockPort GPIOB
#define W5500_clockPin GPIO_Pin_13

#define W5500_SPI 2
#endif

#include "socket.c"
#include "socket.h"
#include "DHCP/dhcp.c"
#include "wizchip_conf.h"
#include "wizchip_conf.c"
#include "W5500/w5500.h"
#include "W5500/w5500.c"

#define DEFAULT_BUFFER_SIZE 768

#ifdef W5500_NETWORK
uint8_t network[4] = {W5500_NETWORK};
uint8_t netmask[4] = {W5500_NETMASK};
#else
uint8_t dhcp_buffer[DEFAULT_BUFFER_SIZE];
uint8_t DHCP_SOCKET = 7;

#endif

wiz_NetInfo net_info;

uint16_t w5500_timer = 0;
uint16_t w5500_port_number = 0;

void SPIReadWrite(uint8_t data)
{
#if W5500_SPI == 1
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;
	SPI_I2S_SendData(SPI1, data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_I2S_ReceiveData(SPI1);
#else if W5500_SPI == 2
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
		;
	SPI_I2S_SendData(SPI2, data);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_I2S_ReceiveData(SPI2);
#endif
}

uint8_t w5500_initialized = 0;
uint8_t w5500_ip_assigned = 0;
uint8_t w5500_connection_inprogress = 1;

uint8_t w5500_data_received = 0;

void chip_on(void)
{
	GPIO_ResetBits(W5500_csPort, W5500_csPin);
}
void chip_off(void)
{
	GPIO_SetBits(W5500_csPort, W5500_csPin);
}
void chip_reset(void)
{
	GPIO_ResetBits(W5500_resetPort, W5500_resetPin);
	delay_ms(1000);
	GPIO_SetBits(W5500_resetPort, W5500_resetPin);
	delay_ms(2000);
}

#ifndef W5500_NETWORK
/* handler of ip assigned */
void W5500_ip_assign(void)
{
	w5500_ip_assigned = 1;
	setSIPR(DHCP_allocated_ip);
	setSUBR(DHCP_allocated_sn);
	setGAR(DHCP_allocated_gw);
}

/* handler of ip changed */
void W5500_ip_update(void)
{
	/* WIZchip Software Reset */
	setMR(MR_RST);
	getMR(); // for delay
	W5500_ip_assign();
	setSHAR(DHCP_CHADDR);
}

/* handler of ip changed */
void W5500_ip_conflict(void)
{
	w5500_ip_assigned = 0;
	LEDBLINKFAST(15);
	// WIZchip Software Reset
	setMR(MR_RST);
	getMR(); // for delay
	setSHAR(DHCP_CHADDR);
}
#endif

int w5500_ini()
{
	LEDBLINK(15);
	w5500_initialized = 0;
	chip_reset();
	net_info.mac[0] = 0xAA;
	net_info.mac[1] = 0xBB;
	net_info.mac[2] = 0xCC;
	net_info.mac[3] = 0xDD;
	net_info.mac[4] = 0xEE;
	net_info.mac[5] = device_index;
#ifdef W5500_NETWORK
	net_info.ip[0] = network[0];
	net_info.ip[1] = network[1];
	net_info.ip[2] = network[2];
	net_info.ip[3] = device_index;
	net_info.sn[0] = netmask[0];
	net_info.sn[1] = netmask[1];
	net_info.sn[2] = netmask[2];
	net_info.sn[3] = netmask[3];
	net_info.gw[0] = network[0];
	net_info.gw[1] = network[1];
	net_info.gw[2] = network[2];
	net_info.gw[3] = 1;
	net_info.dhcp = NETINFO_STATIC;
#else
	net_info.dhcp = NETINFO_DHCP;
#endif

	uint8_t temp;
	uint8_t W5500FifoSize[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2}};
	chip_off();
	reg_wizchip_spi_cbfunc(SPIReadWrite, SPIReadWrite);
	/* CS function register */
	reg_wizchip_cs_cbfunc(chip_on, chip_off);
	if (ctlwizchip(CW_INIT_WIZCHIP, (void *)W5500FifoSize) == -1)
	{
		return -1;
	}

	do
	{
		if (ctlwizchip(CW_GET_PHYLINK, (void *)&temp) == -1)
		{
			return -1;
		}
	} while (temp == PHY_LINK_OFF);

#ifndef W5500_NETWORK
	setSHAR(net_info.mac);
	DHCP_init(DHCP_SOCKET, dhcp_buffer);
	reg_dhcp_cbfunc(
		W5500_ip_assign,
		W5500_ip_update,
		W5500_ip_conflict);
	while (!w5500_ip_assigned)
	{
		DHCP_run();
	}
#else
	wizchip_setnetinfo(&net_info);
#endif
	// set retries
	setRCR(3);
	// set timeout (1=100 us)
	setRTR(20);
	w5500_initialized = 1;
	LEDON(15);
	return 1;
}

void w5500_int()
{
	w5500_timer++;
	// every 1 second (1000ms)
	if (w5500_timer >= 1000)
	{
#ifndef W5500_NETWORK
		DHCP_time_handler();
#endif
		// resetting timer
		w5500_timer = 0;
	}
}

// SERVER MODE
#define MAX_PATH_SIZE 20
#define MAX_ARGS_SIZE 129

struct HttpRequest
{
	uint16_t status_code;
	char request[DEFAULT_BUFFER_SIZE];
	char response[DEFAULT_BUFFER_SIZE];
	char method[10];
	char path[MAX_PATH_SIZE];
	char args[MAX_ARGS_SIZE];
};

// SERVER HANDLER STATUS
#define HTTP_IDLE 0
#define HTTP_RECEIVED 1
#define HTTP_SENT 2
#define HTTP_ERROR 3

void http_response_code_to_str(uint16_t code, char *temp)
{
	switch (code)
	{
	case 200:
		strcpy(temp, "200 OK");
		break;
	case 400:
		strcpy(temp, "400 Bad Request");
		break;
	case 201:
		strcpy(temp, "201 Created");
		break;
	case 401:
		strcpy(temp, "401 Unauthorized");
		break;
	case 403:
		strcpy(temp, "403 Forbidden");
		break;
	case 404:
		strcpy(temp, "404 Not Found");
		break;
	case 405:
		strcpy(temp, "405 Method Not Allowed");
		break;
	case 500:
		strcpy(temp, "500 Internal Server Error");
		break;
	default:
		strcpy(temp, "200 OK");
		break;
	}
}

/// @brief Parses string and returns key&value from string such as param1=1&param2=0&param3=string
/// @param str address of 1st element in string
/// @param key address for return key
/// @param value address for return value
/// @return length of found key+value. If 0 - no more key/value pairs. If > 0 add it to str
uint16_t get_param(char *str, char *key, char *value)
{
	key[0] = '\0';
	value[0] = '\0';
	int16_t equal_position = str_get_pos(str, "=");
	if (equal_position < 0)
		return 0;
	int16_t delimiter_position = str_get_pos(str, "&");
	if (delimiter_position < 0)
	{
		strncpy(key, str, equal_position);
		key[equal_position] = '\0';
		strcpy(value, str + equal_position + 1);
		return equal_position + strlen(value);
	}
	else
	{
		strncpy(key, str, equal_position);
		key[equal_position] = '\0';
		strncpy(value, str + equal_position + 1, delimiter_position - equal_position - 1);
		value[delimiter_position - equal_position - 1] = '\0';
		return ++delimiter_position;
	}
}

int8_t parse_http_request(struct HttpRequest *http_request, char *buf)
{
	// Initialize the response structure
	http_request->method[0] = '\0';
	http_request->path[0] = '\0';
	http_request->request[0] = '\0';
	// Parse method
	if (str_get_pos(buf, "GET") >= 0)
	{
		strcpy(http_request->method, "GET");
	}
	else if (str_get_pos(buf, "POST") >= 0)
	{
		strcpy(http_request->method, "POST");
	}
	else
	{
		return -1;
	}
	// Parse path
	int16_t path_position = str_get_pos(buf, "/");
	if (path_position < 0)
	{ // Path not found
		return -2;
	}
	int16_t args_position = str_get_pos(buf, "?");
	int16_t proto_version_position = str_get_pos(buf, "HTTP/"); // HTTP/1.1
	if (args_position < 0 || args_position > proto_version_position)
	{ // No need to parse args
		for (uint16_t i = 0; i < proto_version_position - path_position; i++)
		{
			if (i + 1 == MAX_PATH_SIZE || i == proto_version_position - path_position - 1)
			{
				http_request->path[i] = '\0';
				break;
			}
			else
				http_request->path[i] = buf[path_position + i];
		}
		http_request->args[0] = '\0';
	}
	else
	{ // Parsing args
		for (uint16_t i = 0; i < args_position - path_position + 1; i++)
		{
			if (i + 1 == MAX_PATH_SIZE || i == args_position - path_position)
			{
				http_request->path[i] = '\0';
				break;
			}
			else
				http_request->path[i] = buf[path_position + i];
		}
		for (uint16_t i = 0; i < proto_version_position - args_position - 1; i++)
		{
			if (i + 1 == MAX_ARGS_SIZE || i == proto_version_position - args_position - 2)
			{
				http_request->args[i] = '\0';
				break;
			}
			else
				http_request->args[i] = buf[args_position + i + 1];
		}
	}

	// Parse Content-Length
	int16_t content_length_position = str_get_pos(buf, "Content-Length:");
	if (content_length_position < 0)
	{ // Content-Length not found
		return 1;
	}

	uint16_t content_length = get_int_from_str(buf + content_length_position + 16);

	// Find the start of the body
	int16_t body_position;
	body_position = str_get_pos(buf, "\r\n\r\n");
	if (body_position > 0)
	{
		body_position += 4;

		if (body_position + content_length >= DEFAULT_BUFFER_SIZE)
			content_length = DEFAULT_BUFFER_SIZE - body_position; // Limit body length

		for (int i = 0; i < content_length; i++)
		{
			http_request->request[i] = buf[body_position + i];
		}
		http_request->request[content_length] = '\0'; // Null-terminate
	}
	return 1;
}

int32_t http_server_process(uint8_t sn, uint16_t port, struct HttpRequest *http_request)
{
	int32_t ret;
	uint16_t size = 0, sentsize = 0;
	char buf[DEFAULT_BUFFER_SIZE];

	// If no physical link - re-init W5500
	if (wizphy_getphylink() != PHY_LINK_ON)
	{
		w5500_ini();
	}

	switch (getSn_SR(sn))
	{
	case SOCK_ESTABLISHED:
		if (getSn_IR(sn) & Sn_IR_CON)
		{
			setSn_IR(sn, Sn_IR_CON);
		}

		if ((size = getSn_RX_RSR(sn)) > 0 && http_request->request[0] == '\0') // Don't need to check SOCKERR_BUSY because it doesn't not occur.
		{
			if (size > DEFAULT_BUFFER_SIZE)
				size = DEFAULT_BUFFER_SIZE;
			ret = recv(sn, buf, size);
			if (ret <= 0)
				return HTTP_ERROR; // check SOCKERR_BUSY & SOCKERR_XXX. For showing the occurrence of SOCKERR_BUSY.
			if (parse_http_request(http_request, buf) < 0)
			{
				return HTTP_ERROR;
			}
			return HTTP_RECEIVED;
		}
		else if (http_request->response[0] != '\0')
		{
			char buff[DEFAULT_BUFFER_SIZE];
			char status_str[30];
			http_response_code_to_str(http_request->status_code, status_str);
			xsprintf(buff, "HTTP/1.1 %s\nContent-type: application/json\nContent-Length: %d\nConnection: close\n\n%s", status_str, strlen(http_request->response), http_request->response);
			uint16_t len = strlen(buff);
			while (len > 0)
			{
				int32_t ret = send(sn, buff, len);
				if (ret == SOCK_BUSY)
					continue;
				else if (ret <= 0)
				{
					close(sn);
					return HTTP_ERROR;
				}
				len -= ret;
			}
			disconnect(sn);
			http_request->response[0] = '\0';
			http_request->request[0] = '\0';
			return HTTP_SENT;
		}

		break;
	case SOCK_CLOSE_WAIT:
		if ((ret = disconnect(sn)) != SOCK_OK)
			return HTTP_ERROR;
		break;
	case SOCK_INIT:
		if ((ret = listen(sn)) != SOCK_OK)
			return HTTP_ERROR;
		break;
	case SOCK_CLOSED:
		if ((ret = socket(sn, Sn_MR_TCP, port, 0x00)) != sn)
			return HTTP_ERROR;
		break;
	default:
		break;
	}
	return HTTP_IDLE;
}
