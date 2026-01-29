# Wearable AI Pin – Hiring Challenge

## Overview
This project presents a conceptual design and firmware implementation for a wearable AI assistant (“AI Pin”).  
The device is designed to operate under strict power constraints while maintaining user privacy and reliable audio capture.

---

## Hardware Architecture

### Dual-Core Low-Power Design
To solve the always-listening power problem, a dual-core System-on-Chip (SoC) is used.

- **Core B (Low-Power Core)**
  - Always ON
  - Handles microphone input
  - Performs wake-word detection
  - Ultra-low power consumption

- **Core A (High-Performance Core)**
  - Normally in sleep mode
  - Activated only after wake-word detection
  - Handles Wi-Fi, cloud communication, and LLM processing

This architecture ensures long battery life while maintaining responsiveness.

---

## Audio Memory Calculation

**Given Parameters:**
- Sample Rate: 16 kHz  
- Bit Depth: 16-bit (2 bytes per sample)  
- Channels: Mono  
- Duration: 10 seconds  

**Calculation:**
- Samples per second = 16,000  
- Bytes per second = 16,000 × 2 = 32,000 bytes  
- Total for 10 seconds = 320,000 bytes ≈ 312.5 KB  

**Conclusion:**
The required buffer exceeds the available 256 KB SRAM.  
A streaming or ring-buffer approach is required to process audio in chunks.

---

## Privacy Hardware Design

To guarantee absolute user privacy, a physical hardware mute switch is implemented.

- The switch directly disconnects the microphone power line
- It is independent of software control
- Even in case of firmware crash, the microphone remains OFF

This ensures hardware-enforced privacy.

---

## Firmware Logic

The firmware is implemented as a finite state machine with the following states:

- **IDLE**: Default state, LED OFF, audio OFF
- **LISTENING**: Button pressed, LED GREEN, audio streaming active
- **ERROR**: Low battery, LED RED, audio disabled

Safety logic forces a return to IDLE if the button is held longer than 30 seconds.

---

## Technologies Used
- Embedded C
- State Machine Design
- Low-Power SoC Architecture
- Audio Streaming Concepts

---

## Author
Saiteja  
Electronics and Communication Engineering
