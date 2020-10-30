test: dist/test.exe
	# running test #
	./$<

dist/StringSet.o: src/lib/StringSet.c
	# building StringSet object #
	gcc -c -o $@ $<

dist/HashMap.o: src/lib/HashMap.c
	# building HashMap object #
	gcc -c -o $@ $<

dist/Array.o: src/lib/Array.c
	# building Array object #
	gcc -c -o $@ $<

dist/test.exe: src/test.c dist/HashMap.o dist/StringSet.o dist/Array.o
	# compiling $@ #
	gcc -o $@ $^

/usr/local/include/cstructures/: ./src/include/*.h
	mkdir -p $@
	cp -v $^ $@

dist/libcstructures.a: dist/StringSet.o dist/HashMap.o dist/Array.o
	ar -rc $@ $^

/usr/local/lib/libcstructures.a: dist/libcstructures.a
	cp -vf $< $@

install: /usr/local/include/cstructures/ /usr/local/lib/libcstructures.a
	ldconfig
	# 						  #
	# successfully installed! #
	# 						  #

uninstall:
	rm /usr/local/include/cstructures/*.h
	rmdir /usr/local/include/cstructures/
	rm /usr/local/lib/libcstructures.a

clean:
	rm -fv dist/*
