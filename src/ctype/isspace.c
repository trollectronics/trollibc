int isspace(int c) {
	switch((char) c) {
		case ' ':
		case '\r':
		case '\n':
		case '\t':
		case '\f':
		case '\v':
			return 1;
	}
	return 0;
}
