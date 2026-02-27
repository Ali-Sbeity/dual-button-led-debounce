# dual-button-led-debounce
Simultaneous dual button LED control with hardware (RC) and software debounce, FSM based logic, and 5-second timed activation


# Simultaneous Dual-Button LED Activation with Hardware & Software Debounce

### A Robust Embedded Input Handling Case Study


## 1. Project Overview
This project implements a synchronized dual-button activation system using an Arduino-based microcontroller.

The LED turns ON for exactly 5 seconds only when both push-buttons are pressed simultaneously, and then turns OFF automatically. The system prevents retriggering until both buttons are released.

Although functionally simple, this project is intentionally designed as a reliable embedded input handling case study, integrating:

- Hardware debounce (RC filter)
- Software debounce (time-based digital filtering)
- Finite State Machine (FSM) architecture
- Non-blocking timing
- Tolerance-aware design
- Frequency-domain reasoning


## 2. Demonstration Vedio
A short demonstration of the system in operation is available here:
The video shows:
- Simultaneous button activation
- Stable LED triggering
- 5-second timed operation
- Retrigger prevention behavior


## 3. System Specification
# Functional Requirements
- Two buttons must be pressed simultaneously.
- LED turns ON for 5 seconds.
- LED turns OFF automatically after 5 seconds.
- No retriggering while buttons remain pressed.
- System returns to IDLE only after both buttons are released.


## 4. System-Level Architecture


This layered architecture increases robustness:
- Hardware layer reduces high-frequency noise.
- Software layer confirms stable logical transitions.
- FSM guarantees deterministic system behavior.


## 5. Mechanical Bounce Analysis
Mechanical push-buttons typically exhibit bounce durations of:
5 ms to 20 ms

During state transitions, the signal oscillates rapidly:
1 0 1 0 1 1 0 1 ...

Without filtering, the MCU may interpret a single press as multiple events.

## 6. Hardware Debounce Design (RC Filter)
# 5.1 Time Constant
The RC time constant:

First-order RC filter transfer function:
