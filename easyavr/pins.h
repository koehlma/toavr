/*
 * Copyright (C) 2015, Maximilian K�hl <mail@koehlma.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PINS_H_
#define PINS_H_

#include <inttypes.h>

#include <avr/io.h>

#define LOW		0
#define HIGH	1

#define INPUT	0
#define OUTPUT	1

template<typename Port, int number> struct Pin {
	static inline void output() {
		Port::ddr::set(Port::ddr::get() | (1 << number));
	}
	static inline void input() {
		Port::ddr::set(Port::ddr::get() & ~(1 << number));
	}
	
	static inline uint8_t mode() {
		return Port::ddr::get() & (1 << number) != 0;
	}
	static inline void mode(uint8_t val) {
		val ? output() : input();
	}
	
	static inline void set() {
		Port::port::set(Port::port::get() | (1 << number));
	}
	static inline void set(uint8_t val) {
		val ? set() : clear();
	}
	static inline uint8_t get() {
		return (Port::port::get() & (1 << number)) != 0;
	}
	static inline void clear() {
		Port::port::set(Port::port::get() & ~(1 << number));
	}
	static inline void toggle() {
		Port::port::set(Port::port::get() ^ (1 << number));
	}
	
	static inline uint8_t read() {
		return (Port::pin::get() & (1 << number)) != 0;
	}
	static inline void write(uint8_t val) {
		set(val);
	}
	
	static inline void pullup() {
		set();
	}
	static inline void pulldown() {
		clear();
	}
	
	static inline void high() {
		set();
	}
	static inline void low() {
		clear();
	}
};

#define _MAKE_PORT(STRUCTNAME, PRT) struct STRUCTNAME {		\
	REGISTER8(ddr, DDR##PRT);								\
	REGISTER8(port, PORT##PRT);								\
	REGISTER8(pin, PIN##PRT);								\
}
#define MAKE_PORT(PRT) _MAKE_PORT(Port##PRT, PRT)

#ifdef DDRA
	MAKE_PORT(A);
#endif

#ifdef DDRB
	MAKE_PORT(B);
#endif

#ifdef DDRC
	MAKE_PORT(C);
#endif

#ifdef DDRD
	MAKE_PORT(D);
#endif

#ifdef DDRE
	MAKE_PORT(E);
#endif

#ifdef DDRF
	MAKE_PORT(F);
#endif

#ifdef DDRG
	MAKE_PORT(G);
#endif

#ifdef DDRH
	MAKE_PORT(H);
#endif

#ifdef DDRI
	MAKE_PORT(I);
#endif

#ifdef DDRJ
	MAKE_PORT(J);
#endif

#ifdef DDRK
	MAKE_PORT(K);
#endif

#ifdef DDRL
	MAKE_PORT(L);
#endif

#endif