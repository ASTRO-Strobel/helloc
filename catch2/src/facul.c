int facul(int f) {
    if (f <= 0) return 1;
    
    int result = 1;
    for (int i = f; i > 1; i--)
        result *= i;
    
    return result;
}
