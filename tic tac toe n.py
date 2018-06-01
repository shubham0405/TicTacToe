# this is code for N*N tic tac toe
# for 4*4 and above cases, the rules for victory include n moves of one kind in a row,a column or a diagonal
# all other possibilities of victory have been neglected
import math
def print_matrix(matrix):
    for i in range(n):
        print(matrix[i])
def check(matrix):
    # checks if there is any space left to play move next moves
    f=0
    for i in range(n):
        for j in range(n):
            if matrix[i][j]=='-':
                f=1
                break
        if f==1:
            break
    if f==1:
        return False
    else:
        return True
def game_over(matrix):
    s_comp = 0
    s_user = 0
    for i in range(n):
        if(matrix[i][i]==comp_inpt):
            s_comp = s_comp + 1
        elif(matrix[i][i]==usr_inpt):
            s_user = s_user + 1
    if(s_comp==n):
        return -100
    elif(s_user==n):
        return 100
    s_comp = 0
    s_user = 0
    for i in range(n):
        if(matrix[i][n-i-1]==comp_inpt):
            s_comp = s_comp + 1
        elif(matrix[i][n-i-1]==usr_inpt):
            s_user = s_user + 1
    if(s_comp==n):
        return -100
    elif(s_user==n):
        return 100
    # diagonals checked
    for i in range(n):
    	s_comp = 0
        s_user = 0
        for j in range(n):
            if(matrix[i][j]==comp_inpt):
                s_comp = s_comp+1
            elif(matrix[i][j]==usr_inpt):
                s_user = s_user+1
        if(s_comp==n):
            return -100
            break
        elif(s_user==n):
            return 100
            break
    # rows checked
    for i in range(n):
    	s_comp = 0
        s_user = 0
        for j in range(n):
            if(matrix[j][i]==comp_inpt):
                s_comp = s_comp+1
            elif(matrix[j][i]==usr_inpt):
                s_user = s_user+1
        if(s_comp==n):
            return -100
            break
        elif(s_user==n):
            return 100
            break
    # columns checked
    return 0
def move(matrix):
    x=int(input("enter the row no."))
    y=int(input("enter the column no."))
    # elimination of all the wrong inputs
    while ((x>n or x<1 or y<1 or y>n) or (matrix[x-1][y-1]!='-')):
        x=int(input("enter the row no."))
        y=int(input("enter the column no."))
    matrix[x-1][y-1]=usr_inpt
    print_matrix(matrix)
    return
def minimax(matrix,dep,usr_turn,alpha,beta):
    if game_over(matrix):
    	return game_over(matrix)
    elif dep==5:
        return 0
    if check(matrix):
        return 0
    # base cases checked
    if not usr_turn:
        f=0
        bestVal=1000
        for i in range(n):
        	for j in range(n):
                        if matrix[i][j]=='-':
                        	matrix[i][j]=comp_inpt
                                value=minimax(matrix,dep+1,not usr_turn,alpha,beta)
        	                bestVal=min(value,bestVal)
				beta=min(bestVal,beta)
                                matrix[i][j]='-'
                            	if(beta<alpha):
                                	f=1
                                	break
            	if(f==1):
                	break
        return bestVal-dep
    # computer played its chance to check other moves
    else:
        f=0
        bestVal=-1000
        for i in range(n):
        	for j in range(n):
                        if matrix[i][j]=='-':
                        	matrix[i][j]=usr_inpt
                                value=minimax(matrix,dep+1,not usr_turn,alpha,beta)
        	                bestVal=max(value,bestVal)
				alpha=max(alpha,bestVal)
                                matrix[i][j]='-'
                            	if(beta<alpha):
                                	f=1
                                	break
            	if(f==1):
                	break
        return bestVal-dep
    # computer played other player's chance to check other moves
def bestMove(matrix):
    bestMove = [-1,-1]
    bestVal=1000
    for i in range(n):
    	for j in range(n):
        	if matrix[i][j]=='-':
                    matrix[i][j]=comp_inpt
                    val=minimax(matrix,0,True,-1000,1000)
                    print(val)
                    matrix[i][j]='-'
                    if val<bestVal:
                        bestMove=[i,j]
                        bestVal=val
    return bestMove
# main code
n=int(input("select the number of rows u want in ur game"))
matrix=[['-' for i in range(n)]for i in range(n)]
usr_inpt=int(input("please choose either 0 or 1"))
comp_inpt=1-usr_inpt
i=1
if comp_inpt:
    while True:
    # comp's move
        vec=bestMove(matrix)
        if vec==[-1,-1]:
    	    print("oops!!!")
            break
        else:
            xi,yi=vec[0],vec[1]
    	    matrix[xi][yi]=comp_inpt
            print_matrix(matrix)
        if game_over(matrix)==100:
    	    print("Congrats u hve dn impossible!!!")
            break
        elif game_over(matrix)==-100:
    	    print("better luck next time")
    	    break
        elif i >= n*n:
            print("draw!!!")
            break
        i=i+1
        # user's move
        move(matrix)
        if game_over(matrix)==100:
    	    print("Congrats u hve dn impossible!!!")
            break
        elif game_over(matrix)==-100:
    	    print("better luck next time")
    	    break
        elif i >= n*n:
            print("draw!!!")
            break
        i=i+1
else:
    while True:
        # user's move
        move(matrix)
        if game_over(matrix)==100:
    	    print("Congrats u hve dn impossible!!!")
            break
        elif game_over(matrix)==-100:
    	    print("better luck next time")
    	    break
        elif i >= n*n:
            print("draw!!!")
            break
        i=i+1
        # comp's move
        vec=bestMove(matrix)
        if vec==[-1,-1]:
    	    print("oops!!!")
            break
        else:
            xi,yi=vec[0],vec[1]
    	    matrix[xi][yi]=comp_inpt
            print_matrix(matrix)
        if game_over(matrix)==100:
    	    print("Congrats u hve dn impossible!!!")
            break
        elif game_over(matrix)==-100:
    	    print("better luck next time")
    	    break
        elif i >= n*n:
            print("draw!!!")
            break
        i=i+1
