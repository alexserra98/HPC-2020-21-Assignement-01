setwd("/home/alex/Desktop/uni/HPC/")
file<-read.csv("tmp.csv")
df <- data.frame(bytes=file[,1], time=file[,2], band=file[,3],ctime=file[,5],cband=file[,6])
x<-seq(2,28)

fit<-lm(df$time ~ df$bytes)
fit
c<-fit$coefficients
y<- df$bytes*c[2]+c[1]
df$comp = y
library(ggplot2)
 ggplot(df, aes(x=x))+
 geom_point(aes(y=bytes/comp,color='Computed',size=2),shape=15)+
   geom_line(aes(y=bytes/comp,color='Computed'))+
 geom_point(aes(y=band,color='Observed',size=2),shape=15)+
   geom_line(aes(y=band,color='Observed'))+
   guides(size="none")+
 ggtitle("Observed vs Computed bandwidth with MPI in the same socket") 
 
 