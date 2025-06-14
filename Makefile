# TFG-FirmwareTests/Makefile

TESTS = uartTest gpioTest timerTest
.PHONY: all clean $(TESTS)

all: $(TESTS)

$(TESTS):
	$(MAKE) -C $@

clean:
	for dir in $(TESTS); do \
		$(MAKE) -C $$dir clean; \
	done
