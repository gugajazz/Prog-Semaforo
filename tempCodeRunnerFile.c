for ( size_t i = 0; i < ROWS; i++ )
    {
    int *tmp = realloc( array[i], sizeof *array[i] * (COLS + 1) );
    if ( tmp )
    {
        array[i] = tmp;
    }