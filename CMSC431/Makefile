all: Proj1

Proj1:
	$(MAKE) -C src

tests: Proj1
	$(MAKE) -C tests

clean:
	-$(RM) Proj1
	cd src && make clean
	cd tests && make clean
