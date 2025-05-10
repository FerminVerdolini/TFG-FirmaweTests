# TFG-FirmwareTests/Makefile

TESTS = uartTest
.PHONY: all clean $(TESTS)

all: $(TESTS)

$(TESTS):
	$(MAKE) -C $@

clean:
	for dir in $(TESTS); do \
		$(MAKE) -C $$dir clean; \
	done
