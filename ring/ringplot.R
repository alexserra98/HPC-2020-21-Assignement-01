setwd("/home/alex/Desktop/uni/HPC/es1_assig1")
file<-read.csv("data.csv")
quad <- function(x){
  return(x^2)
}
q<-quad(file[,1])
df <- data.frame(proc=file[,1], time=file[,2])
df$time10=df$time*10
fit <-lm(df$time ~ df$proc -1)
c<-fit$coefficients
y<-c[2]*df$proc -0.56
library(ggplot2)
ggplot(df, aes(x=proc))+
  geom_point(aes(y=time))+
  geom_line(aes(y=time))+
  geom_line(aes(y=y,color="expected behaviour"))

