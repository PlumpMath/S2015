all: Proj1

Proj1:
	$(MAKE) -C src

tests: Proj1
	$(MAKE) -C tests

clean:
	-$(RM) Proj1
	$(MAKE) -C src clean
	$(MAKE) -C tests clean
