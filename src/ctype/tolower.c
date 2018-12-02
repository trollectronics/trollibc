int tolower(char c) {
	if(c >= 'A' && c <= 'Z')
		c += 'a' - 'A';
		
	return c;
}
