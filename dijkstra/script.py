import subprocess
import matplotlib.pyplot as plt

temp=subprocess.check_output(["./dijkstra"], stderr=subprocess.STDOUT)
array=[]
heap=[]
temp2=temp.split()
plt.title("Dijkstra algorithm")
plt.figure(figsize=(9,6))
for i in range(len(temp2)//2):
    array.append(float(temp2[2*i]))
    heap.append(float(temp2[2*i+1]))
x=[2**i for i in range(4,18)]
print(array)
print(heap)
plt.plot(x,array,label="array")
plt.plot(x,heap,label="heap")
plt.xlabel("size")
plt.ylabel("time (s)")
plt.legend()
