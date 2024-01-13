# 7segment_with_attiny
Digital voltmeter and segment display with attiny 13A
2020.06.28
 * Analog reading of four digit number represent in 7-segment display
 * 
 * Connect voltage divider between Vin,A0,GND.
 * Set Max value.
 * 
 * Segment display is controlled by 74LS595 shift registers
 * pin B to H of first shift register goes to 7 segments
 * pin B to F of second shift register goes to common pins
