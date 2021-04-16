import matplotlib.pyplot as plt
import numpy as np
import sys
import math
import statistics
import mplcursors



def graphics(nombres_archivo,separator,number_separator,organization,name,x_label,y_label,samples,axis):

        files=[]
        legend_names=[]
        temp=[]
        
        colors=["g","r","b","c","m","k"]
        for i in range(len(nombres_archivo)):
                temp=nombres_archivo[i].split("/")
                temp=temp[len(temp)-1].split(".")
                legend_names.append(temp[0])
        for i in range(len(nombres_archivo)):
            archivo=open(nombres_archivo[i],"r")
            files.append(archivo)
        x_array=[]
        y_array=[]
        for file in files:
                guardar(file,x_array,y_array,number_separator,separator)
        columns=[]
        per_graph=[]
        columns, per_graph=graphics_organization(organization,per_graph,columns)
        lengths=[]
        for i in x_array:
                lengths.append(len(i))
        min_samples=min(lengths)
        if(int(samples)<min_samples):
                min_samples=int(samples)
        
        if(len(columns)==1):
                fig, ax=plt.subplots()   
                for i in range(per_graph[0]):
                        ax.plot(x_array[i][0:min_samples],y_array[i][0:min_samples],colors[i],label=legend_names[i])  # Plot some data on the axes.
                        ax.grid(True)
                        ax.set_ylabel(y_label,fontsize=16)
                        ax.set_xlabel(x_label,fontsize=16)
                        ax.set_title(name,fontsize=16)
                        if(axis=="logaritmico"):
                                ax.semilogx()
                        #ax.set(ylim=(0,1000))
                        
                plt.legend(loc='upper right')
                mplcursors.cursor(multiple=True).connect("add", lambda sel: sel.annotation.draggable(False))
                plt.show() 
        else:      
                fig, ax=plt.subplots(1,len(columns))  
                k=0
                for j in range(0,len(columns)):
                        for i in range(per_graph[j]):
                                
                                ax[j].plot(x_array[k][0:min_samples],y_array[k][0:min_samples],colors[i],label=legend_names[i])  # Plot some data on the axes.
                                ax[j].grid(True)
                                ax[j].set_ylabel(y_label,fontsize=16)
                                ax[j].set_xlabel(x_label,fontsize=16)
                                ax[j].set_title(name,fontsize=16)
                                if(axis=="logaritmico"):
                                         ax[j].semilogx()

                                k+=1
                plt.legend(loc='upper right')    
                mplcursors.cursor(multiple=True).connect("add", lambda sel: sel.annotation.draggable(False))
                plt.show()
        
        
                
def guardar(archivo,x_array,y_array,number_separator,separator):
        labels=[]
        temp_x=[]
        temp_y=[]
        if(separator=="tab"):
                separator="\t"
        labels=archivo.readline().split(separator)
        #labels[1]=labels[1].replace("\n","")
        if(number_separator==","):
                for line in archivo:
                        linea=line.split(separator)
                        temp=linea[0].split(",")
                        
                        try:
                                temp_x.append(float(temp[0]+"."+temp[1]))
                                temp=linea[1].split(",")
                                temp_y.append(float(temp[0]+"."+temp[1]))
                        except: 
                                continue
                x_array.append(np.array(temp_x))
                y_array.append(np.array(temp_y))   
        
        if(number_separator=="."):
                for line in archivo:
                        linea=line.split(separator)
                        
                        try:
                                temp_x.append(float(linea[0]))
                                temp_y.append(float(linea[1]))
                        except:
                                continue
                        
                x_array.append(np.array(temp_x))
                y_array.append(np.array(temp_y))
                        
                          

def graphics_organization(organization,per_graph,columns):
        columns=organization.split(";")
        x=[]
        for i in columns:
                x=i.split(",")
                per_graph.append(len(x))
        return columns, per_graph
           
        
