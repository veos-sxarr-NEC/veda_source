#define __cplusplus
PACKAGE := veoffload-veda
VERSION = $(shell cat ../VERSION)
TOP_SRCDIR = $(abspath ../ ./)

edit = sed -e "s,@PACKAGE@,$(PACKAGE),g" \
	-e "s,@VERSION@,$(VERSION),g" \
	-e "s,@top_srcdir@,$(TOP_SRCDIR),g"

ALL: Doxyfile GettingStarted.md

Doxyfile: Doxyfile.in
	echo $(SRCDIR)
	$(edit) $< > $@

GettingStarted.md: GettingStarted.md.in
	$(edit) $< > $@

clean:
	rm -rf Doxyfile GettingStarted.md
