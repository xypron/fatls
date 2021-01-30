# SPDX-License-Identifier: GPL-2.0+

prefix?=/usr/local

all:
	gcc fatls.c -o fatls

check:
	./fatls -h

clean:
	rm -f fatls

install:
	mkdir -p $(DESTDIR)$(prefix)/bin/
	cp fatls $(DESTDIR)$(prefix)/bin/

uninstall:
	rm -f $(DESTDIR)$(prefix)/bin/fatls
