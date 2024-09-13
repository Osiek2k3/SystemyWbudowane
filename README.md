# Systemy Wbudowane - KAmeleon-STM32L4

Repozytorium zawiera projekty z przedmiotu **Systemy Wbudowane**, oparte na płytce ewaluacyjnej **KAmeleon-STM32L4** i napisane w języku C, bez użycia biblioteki STM32 HAL. Główne zadania obejmują konfigurację GPIO, obsługę timerów oraz komunikację UART, z naciskiem na bezpośredni dostęp do rejestrów mikrokontrolera.

## Spis treści
- Opis projektu
- Zadania
  1. Licznik na wyświetlaczu 7-segmentowym
  2. Implementacja timera
  3. Komunikacja UART
- Wymagania
- Instalacja

## Opis projektu
Repozytorium zawiera trzy zadania, które dotyczą kluczowych aspektów programowania systemów wbudowanych z wykorzystaniem mikrokontrolera STM32L4. W każdym zadaniu korzystamy z bezpośredniego dostępu do rejestrów, bez wsparcia bibliotek HAL, co wymaga dogłębnej znajomości dokumentacji mikrokontrolera.

### Główne założenia:
- **Brak użycia HAL**: Wszystkie operacje na rejestrach są wykonywane przez wskaźniki, bez korzystania z biblioteki HAL.
- **STM32CubeIDE**: Projekt został rozwijany w STM32CubeIDE.
- **Interakcja z peryferiami**: Projekty obejmują GPIO, timery i komunikację UART.

## Zadania

### 1. Licznik na wyświetlaczu 7-segmentowym
Celem zadania jest napisanie programu w C, który wykorzysta wyświetlacz 7-segmentowy dostępny na płytce KAmeleon-STM32L4 do wyświetlania licznika.

**Kroki:**
- Analiza schematów połączeń płytki.
- Konfiguracja pinów GPIO odpowiadających za sterowanie wyświetlaczem.
- Implementacja logiki licznika z bezpośrednim dostępem do rejestrów GPIO.

### 2. Implementacja timera
Zadanie to wymaga implementacji opóźnienia z użyciem sprzętowego timera zamiast funkcji HAL_Delay.

**Kroki:**
- Konfiguracja timera (TIM6 lub TIM7).
- Napisanie funkcji `void delay(unsigned ms)` zapewniającej opóźnienie w milisekundach.
- Manipulacja rejestrami timera bezpośrednio przez wskaźniki, bez korzystania z bibliotek HAL.

### 3. Komunikacja UART
Celem tego zadania jest dwukierunkowa komunikacja UART pomiędzy mikrokontrolerem a komputerem, z zamianą wielkości liter w odebranych znakach ASCII.

**Kroki:**
- Konfiguracja UART w trybie 8N1 (8 bitów danych, brak parzystości, 1 bit stopu).
- Odbieranie znaków ASCII, zamiana ich wielkości, a następnie odesłanie z powrotem.
- Testowanie komunikacji za pomocą programu Putty lub innego monitora szeregowego.

## Wymagania
- **STM32CubeIDE**: Środowisko programistyczne dla mikrokontrolerów STM32.
- **Płytka KAmeleon-STM32L4**: Sprzęt wykorzystywany do realizacji zadań.
- **Podstawowa znajomość rejestrów STM32**: Dokumentacja dotycząca GPIO, timerów i UART.
- **Putty lub inny monitor szeregowy**: Do testowania komunikacji UART.

## Instalacja
1. Sklonuj repozytorium:
   ```bash
   git clone https://github.com/twojanazwa/embedded-systems-kameleon-stm32l4.git
2. Otwórz projekt w STM32CubeIDE.
3. Zbuduj i wgraj kod na płytkę KAmeleon-STM32L4.
4. Użyj Putty lub innego monitora szeregowego do testowania komunikacji UART.

# EN
# Embedded Systems - KAmeleon-STM32L4

This repository contains projects developed as part of the **Embedded Systems** course, focused on programming the **KAmeleon-STM32L4** evaluation board in C without using the STM32 HAL library. The main tasks involve configuring GPIO, using timers, and implementing UART communication, with an emphasis on low-level register access.

## Table of Contents
- Project Overview
- Tasks
  1. Counter on a 7-segment display
  2. Timer implementation
  3. UART communication
- Requirements
- Installation

## Project Overview
This repository contains three tasks that cover key concepts in embedded systems programming on the KAmeleon-STM32L4 board. Each task focuses on a specific peripheral or functionality of the STM32 microcontroller, with low-level programming through direct register access instead of using the HAL library.

### Key Assumptions:
- **No HAL usage**: All register operations are done directly using pointers, without relying on the STM32 HAL library.
- **STM32CubeIDE**: The project was developed using STM32CubeIDE.
- **Peripheral interaction**: The tasks involve GPIO, timers, and UART communication.

## Tasks

### 1. Counter on a 7-segment display
The goal of this task is to write a C program that displays a counter on the 7-segment display available on the KAmeleon-STM32L4 board.

**Steps:**
- Analyze the board's schematic to understand the connections between the microcontroller and the 7-segment display.
- Configure the GPIO pins controlling the display.
- Implement counter logic with direct access to the GPIO registers.

### 2. Timer Implementation
This task involves configuring a hardware timer to handle delays, replacing the HAL_Delay function.

**Steps:**
- Configure a basic timer (TIM6 or TIM7).
- Write the `void delay(unsigned ms)` function to provide millisecond delays.
- Directly manipulate the timer registers via pointers, without using HAL structures.

### 3. UART Communication
The goal is to implement bidirectional UART communication between the STM32 microcontroller and a computer, with character case conversion for received ASCII characters.

**Steps:**
- Configure UART for 8N1 communication (8 data bits, no parity, 1 stop bit).
- Receive ASCII characters, convert their case, and send them back.
- Test UART communication using a serial monitor like Putty.

## Requirements
- **STM32CubeIDE**: The development environment for STM32 microcontrollers.
- **KAmeleon-STM32L4 board**: Hardware used for the tasks.
- **Basic STM32 register knowledge**: Familiarity with GPIO, timers, and UART documentation.
- **Putty or another serial monitor**: To test UART communication.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/embedded-systems-kameleon-stm32l4.git
2. Open the project in STM32CubeIDE.
3. Build and upload the code to the KAmeleon-STM32L4 board.
4. Use Putty or another serial monitor to test UART communication.
