test: dist/test.exe
	# running test #
	./$<

dist/Map.o: src/lib/Map.c
	# building Map object #
	gcc -c -o $@ $<

dist/test.exe: src/test.c dist/Map.o
	# compiling $@ #
	gcc -o $@ $^

clean:
	rm -fv dist/*
