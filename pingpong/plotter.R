setwd("/home/alex/Desktop/uni/HPC/es2_assig1")
core <- read.csv("cor.csv")
soc <- read.csv("soc.csv")
nod <- read.csv("nod.csv")
x<-seq(2,28)
df<-data.frame(exp=x, tcor= core[,2], mbcor = core[,3], tsoc= soc[,2], mbsoc = soc[,3],tnod= nod[,2], mbnod = nod[,3])

library(ggplot2)
ggplot(df, aes(x=exp))+
  geom_point(aes(y=mbcor,color='Core',size=2),shape=15)+
  geom_line(aes(y=mbcor,color='Core'))+
  geom_point(aes(y=mbsoc,color='Socket',size=2),shape=16)+
  geom_line(aes(y=mbsoc,color='Socket'))+
  geom_point(aes(y=mbnod,color='Node',size=2),shape=17)+
  geom_line(aes(y=mbnod,color='Node'))+
  guides(size="none")+
  xlab("log2(Mbytes)")+
  ylab("Mbytes/sec")+
  geom_vline(xintercept=14.966, linetype=3)+
  geom_vline(xintercept=19.966, linetype=3)+
  geom_vline(xintercept=24.233, linetype=3)+
  geom_text(aes(x=14.5, label="L1", y=0))+
  geom_text(aes(x=19.5, label="L2", y=0))+
  geom_text(aes(x=23.5, label="L3", y=0))+
  theme(legend.position = c(0.3, 0.7),legend.key.size = unit(2, 'cm'))+
  ggtitle("Benchmarks with MPI using tcp")



