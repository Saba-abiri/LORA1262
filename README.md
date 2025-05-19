
# 🚀 **LoRa1262 STM32 HAL Driver**
A **highly optimized STM32 HAL-based driver** for the **LoRa1262 (SX1262)** module, enabling **LoRa communication** using SPI. This project is built for **STM32CubeIDE** and is designed for **low-power, long-range** wireless communication.

![image](https://github.com/user-attachments/assets/65f4a5bc-200a-4d3e-9188-d99eeec2a38e)
 
 
---   

## 🛠 **Features**
✅ **Full-duplex SPI communication** with SX1262   
✅ **LoRa packet transmission and reception**  
✅ **Interrupt-based packet handling**  
✅ **Standby, Receive, and Transmit modes**  
✅ **Adjustable frequency, bandwidth, spreading factor, and coding rate**  
✅ **Low-power mode for energy efficiency**  
✅ **Error handling & status monitoring**  

---

## 🏗 **Hardware Requirements**
- **LoRa1262 Module (SX1262)**
- **STM32 Microcontroller** (Tested on STM32G0, STM32F4, etc.)
- **SPI-compatible connections**
- **3.3V Power Supply**
- **ST-Link Debugger** (Optional)

---

## 📌 **Pin Configuration (SPI Interface)**
| STM32 Pin | SX1262 Pin | Description |
|-----------|-----------|-------------|
| `MOSI (PA7)` | `MOSI` | SPI Data Input |
| `MISO (PA6)` | `MISO` | SPI Data Output |
| `SCK (PA5)`  | `SCK`  | SPI Clock |
| `NSS (PA4)`  | `NSS`  | Chip Select |
| `RESET (PB0)` | `RESET` | Module Reset |
| `BUSY (PB1)`  | `BUSY`  | Module Busy Pin |
| `DIO1 (PB2)`  | `DIO1`  | Interrupt Pin |
| `GND` | `GND` | Ground |
| `3.3V` | `VCC` | Power Supply |

---

## 📂 **Project Structure**
```
├── Core/
│   ├── Src/             # Source files
│   ├── Inc/             # Header files
│   ├── main.c           # Main application
│   ├── spi.c            # SPI communication
│   ├── gpio.c           # GPIO control
│   ├── uart.c           # Debugging via UART
│   └── stm32_hal/       # HAL Libraries
├── Drivers/             # STM32 HAL Drivers
├── Libs
|   ├── Src/             # Source files
|       ├──SX1262.c
|   ├── SX1262.h
|   ├── SX1262_Definitions.h
├── README.md            # Documentation
├── .gitignore           # Git ignore file
└── LORA_1262f30_Receive.ioc         # STM32CubeMX project file
```

---

## ⚙️ **Software Setup**
### **1️⃣ Clone the Repository**
```sh
git clone https://github.com/Saba-abiri/LORA1262.git
cd LORA1262
```

### **2️⃣ Open in STM32CubeIDE**
- Import the `.ioc` file in **STM32CubeMX**
- Configure **SPI** and **GPIO** settings
- Generate project files

### **3️⃣ Configure SPI in STM32CubeMX**
- **SPI Mode:** SPI Mode 0  
- **Baud Rate:** ≤10MHz  
- **Data Size:** 8-bit  

### **4️⃣ Build & Flash the Firmware**
- Compile the project
- Upload to STM32 using **ST-Link**

---

## 📡 **Usage**
configuration for the SX1262 LoRa transceiver
```c
  SX1262_Get_st()->Busy_Pin = BUSY_LORA_Pin;
	SX1262_Get_st()->Busy_Port= BUSY_LORA_GPIO_Port;
	SX1262_Get_st()->NSS_Pin = NSS_LORA_Pin;
	SX1262_Get_st()->NSS_Port = NSS_LORA_GPIO_Port;
	SX1262_Get_st()->Reset_Pin = NRESET_LORA_Pin;
	SX1262_Get_st()->Reset_Port = NRESET_LORA_GPIO_Port;
	SX1262_Get_st()->SPI = hspi1;
 ```
### **Initialize LoRa1262**
Call the initialization function in `main.c`:
```c
SX1262_Init();
```

### **Send a LoRa Packet**
```c
uint8_t data[] = "Hello, LoRa!";
SX1262_Transmit(data, sizeof(data));
```

### **Receive a LoRa Packet**
set to recive mode
```c
SX1262_setModeReceive();
```
wait till DI01 intterupt appears!
```c
uint8_t rxBuffer[255];
uint8_t packetLength;
SX1262_HandleCallback(rxBuffer, &packetLength);
```

### **Change LoRa Frequency**
```c
SX1262_SetFrequency(433000000); // Set to 433 MHz
```

### **Change Operating Mode**
```c
SX1262_setModeReceive(); // Receive Mode
SX1262_setModeStandby(); // Standby Mode
```

---

## 🔧 **Functions Overview**
| Function | Description |
|----------|-------------|
| `SX1262_Init()` | Initializes the LoRa1262 module |
| `SX1262_Transmit(uint8_t*, uint8_t)` | Sends a LoRa packet |
| `SX1262_HandleCallback(uint8_t*, uint8_t*)` | Handles LoRa packet reception |
| `SX1262_SetFrequency(uint32_t freq)` | Sets the LoRa frequency |
| `SX1262_setModeReceive()` | Switches to Receive Mode |
| `SX1262_setModeStandby()` | Switches to Standby Mode |
| `SX1262_getstatus()` | Gets module status |
| `SX1262_IsBusy()` | Checks if the module is busy |
| `SX1262_BusyWait()` | Waits until the module is free |

---

## ⚠️ **Troubleshooting**
| Issue | Possible Cause | Solution |
|-------|---------------|----------|
| ❌ No response from SX1262 | Incorrect SPI wiring | Check connections |
| ❌ Transmission failure | Wrong frequency or power settings | Verify settings in `SX1262_SetFrequency()` |
| ❌ Packet loss | Low signal strength or interference | Increase power, adjust SF, BW |

---

## 📌 **To-Do**
- [ ] Implement **CRC checks** for packet integrity  
- [ ] Add **FSK modulation support**  
- [ ] Improve **low-power consumption**  

---

## 📜 **License**
This project is open-source under the **MIT License**. Feel free to use, modify, and contribute!  

🔗 **References**:  
- [SX1262 Datasheet](https://www.semtech.com/products/wireless-rf/lora-transceivers/sx1262)  

---

💡 **Developed by [Saba Abiri](https://github.com/Saba-abiri)** 🚀  

---
