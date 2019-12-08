# 1 "queen.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "queen.c"




int Legal_Pos();
int abs();

int main () {
    int rows[8];

    int row, col;
    int found;


    for ( row=0 ; row < 8 ; row++ ) {
        rows[row] = -1;
    }




    for ( row=0 ; row < 8 ; row++ ) {
        found = 0;
        for ( col=0 ; (col < 8) && !found ; col++ ) {
            if ( Legal_Pos (row, col, rows) ) {
                rows[row] = col;
                found = 1;
            }
        }
    }

    return(abs(-5));
}
# 50 "queen.c"
int Legal_Pos (int row, int col, int rows[8])
{
    int i;


    for ( i=0 ; i < 8 ; i++ ) {
        if ( i != row ) {

            if ( rows[i] != -1 ) {




                if ( (abs(col-rows[i]) == abs(i-row)) ||
                     (col == rows[i]) ) {
                    return(0);
                }
            }
        }
    }


    return(1);
}
