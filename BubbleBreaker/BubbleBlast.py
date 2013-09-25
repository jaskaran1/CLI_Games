import numpy as np
import random
from collections import deque
def bfs(A,i,j,disc,m,n):
    "Searches the grid to return a connected component"
    component=[]
    Q=deque()#use this for BFS
    Q.append([i,j])
    c=A[i][j]
    disc[i][j]=1
    while len(Q)>0:
        u=Q.popleft()
        i,j=u
        component.append([i,j])
        if i-1>=0 and A[i-1][j]==c and disc[i-1][j]==0:
            Q.append([i-1,j])#up
            disc[i-1][j]=1
        if j-1>=0 and A[i][j-1]==c and disc[i][j-1]==0:
            Q.append([i,j-1])#left
            disc[i][j-1]=1
        if j+1<n and A[i][j+1]==c and disc[i][j+1]==0:
            Q.append([i,j+1])#right
            disc[i][j+1]=1
        if i+1<m and A[i+1][j]==c and disc[i+1][j]==0:
            Q.append([i+1,j]);#down
            disc[i+1][j]=1
    return component

def burst(A,c,m,n):
    "We burst the entire same colored component and modify the grid so that any empty space can only have a bubble to the right/below"
    for node in c:#for shifting columns down
        i,j=node#coordinates of the bubble to be burst
        A[i][j]=-1
        for k in xrange(i-1,-1,-1):#we shift the entire column down
            A[k+1][j]=A[k][j]
        A[0][j]=-1
    #print "After shifting columns down",A    
    for j in xrange(n-1,-1,-1):#for shifting columns right
        flag=0
        for x in A[:,j]:
            if x!=-1:#we don't delete column
                flag=1
                break
        if flag==0:#delete column and shift content to right            
            for k in xrange(j-1,-1,-1):#shift the array to right
                A[:,k+1]=A[:,k]
            A[:,0]=(-1)*np.ones((m,1)).squeeze()                
    
def Solver1(A,score,m,n,disc,maxim,L,Sol):
    "Exhaustive approach by recursion.Returns the list"
    components=[]#list of connected components of A
    disc[:]=0#initialising all nodes as undiscovered
    for i in xrange(m):
        for j in xrange(n):
            if A[i][j]!=-1:# an unburst bubble
                l=bfs(A,i,j,disc,m,n)
                components.append(l)
    flag=0
    for c in components:
        if(len(c)>1):
            flag=1
            Acopy=np.copy(A)#create a copy
            burst(Acopy,c,m,n)#it burst the bubbles of the component c in A and modifies A
            L.append([Acopy,len(c)**2])#the burst matrix is appended                                
            Sol=Solver1(Acopy,score+len(c)**2,m,n,disc,maxim,L,Sol)
            maxim=Sol[-1]#the maximum currently
            L.pop()#the last state is undone or discarded
            #A=Acopy#A refers to the unchanged version
    if flag==0:#No bubble left to burst.The game ends ie this is the leaf node in the game tree
        if score>maxim:
            #print score
            maxim=score
            Sol=L[:]
            Sol.append(score)
    return Sol

def Solver2(A,m,n,disc,Sol,score):
    "Burst the component with maximum bubbles"
    score=0
    Acopy=np.copy(A)#copy of A.So that changes to A aren't reflected outside.Copy by value
    #I=0
    while(1):
        #I=I+1
        #print str(I)+"th iteration"
        components=[]
        disc[:]=0
        for i in xrange(m):
            for j in xrange(n):
                if Acopy[i][j]!=-1:# an unburst bubble
                    l=bfs(Acopy,i,j,disc,m,n)
                    components.append(l)
        #print "No of components=",len(components)            
        if len(components)>0:            
            maxim=len(components[0])
        else:#game over all bubble gone
            #print "Game over all finished."
            Sol.append(score)
            break    
        b=components[0]#initializing component which will be burst
        for c in components:
            if len(c)>maxim:
                maxim=len(c)
                b=c
        if maxim==1:#this means game over
            #print "Game over"
            Sol.append(score)
            break
        burst(Acopy,b,m,n)
        Mcopy=np.copy(Acopy)
        Sol.append([Mcopy,len(b)**2])
        score=score+len(b)**2            
                        
    
    
def Solver3(A,m,n,disc,Sol,score):
    "Burst a component at random"
    score=0
    Acopy=np.copy(A)
    while(1):
        #I=I+1
        #print str(I)+"th iteration"
        components=[]
        disc[:]=0
        for i in xrange(m):
            for j in xrange(n):
                if Acopy[i][j]!=-1:# an unburst bubble
                    l=bfs(Acopy,i,j,disc,m,n)
                    components.append(l)
        #print "No of components=",len(components)            
        if len(components)==0:            
            Sol.append(score)
            break
        breakable=[]#contains those components which can be burst    
        for c in components:
            if len(c)>1:
               breakable.append(c)
        if len(breakable)==0:
            Sol.append(score)
            break               
        b=breakable[random.randrange(0,len(breakable))]#random component which will be burst
        burst(Acopy,b,m,n)
        Mcopy=np.copy(Acopy)
        Sol.append([Mcopy,len(b)**2])
        score=score+len(b)**2       

#########################################################################################################################################
random.seed()#initialize for random                               
m=int(raw_input("Rows"))
n=int(raw_input("Cols"))
c=int(raw_input("Color"))#colors from 0 to c-1.(Optional)
A=np.zeros((m,n))#initialized
for i in xrange(m):
    for j in xrange(n):
        A[i][j]=int(raw_input())
#A=np.array([[0,3,1,1,1,1],#an actual easy game on which backtracking is slow.example on which it is too slow.Highest score-464(randomize)
#            [2,1,0,2,2,2],
#            [2,3,0,2,0,0],
#            [3,1,1,2,1,3],
#            [3,1,1,2,0,3],
#            [3,1,2,3,2,3],
#            [3,1,3,3,2,3],
#            [3,2,3,2,2,3],
#            [2,2,1,0,0,1]])
#input of the matrix        
#print A
#A=np.array([[0,3,1,1,1,1],#backtracking working for works for <=24 elements only
#            [2,1,0,2,2,2],
#            [2,3,0,2,0,0],
#            [3,1,1,2,1,3],
#            [3,1,1,2,0,3]])

components=[]#stores list of conected components of matrix
disc=np.zeros((m,n))#disc[i][j] tells if the bubble[i][j] is discovered or not
score=0
maxim=0
L=[[A,0]]
Sol=[[A,0]]#the list which contains the optimal solution of the matrix step by step with answer
if m*n<31:
    Sol=Solver1(A,score,m,n,disc,maxim,L,Sol)
    for i in xrange(len(Sol)-1):
        print Sol[i]
    print "Highest score by solver1(exhaustive recursion)=",Sol[-1]
Sol=[[A,0]]
Solver2(A,m,n,disc,Sol,score)
for i in xrange(len(Sol)-1):
    print Sol[i]
print "Highest score by solver2(pick max)=",Sol[-1]
it=700
maxim=0
Sol=[]
for i in xrange(1,it+1):
    L=[[A,0]]
    Solver3(A,m,n,disc,L,score)
    if L[-1]>maxim:
         maxim=L[-1]
         Sol=L    
for i in xrange(len(Sol)-1):
    print Sol[i]
print "Highest score by solver3(random) in %d iterations=" % (it),Sol[-1]           
