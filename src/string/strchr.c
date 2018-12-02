char *strchr(char *str, char chr) {
	for (; *str; str++)
		if (*str == chr)
			return str;
	return NULL;
}
