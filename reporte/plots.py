import csv, math, collections
import numpy as np, matplotlib
matplotlib.use("Agg"); import matplotlib.pyplot as plt
rows=list(csv.DictReader(open("results.csv")))
C=["#2a78d6","#eb6834","#1baf7a","#eda100","#e87ba4"]; MK=["o","s","^","D","v"]
INK="#0b0b0b"; INK2="#52514e"
plt.rcParams.update({"font.size":9,"axes.edgecolor":INK2,"axes.labelcolor":INK,"xtick.color":INK2,"ytick.color":INK2,
 "axes.spines.top":False,"axes.spines.right":False,"axes.grid":True,"grid.color":"#e4e3df","grid.linewidth":0.6,"lines.linewidth":2,"lines.markersize":5,"figure.facecolor":"white","axes.facecolor":"white"})
dists=["square","disk","parabola"]
# (a) h vs n
fig,ax=plt.subplots(figsize=(5.6,3.6))
for k,d in enumerate(dists):
    pts=sorted({(int(r["n"]),int(r["h"])) for r in rows if r["dist"]==d and r["algo"]=="graham"})
    n=[p[0] for p in pts]; h=[p[1] for p in pts]
    s=np.polyfit(np.log10(n),np.log10(h),1)[0]
    ax.plot(n,h,marker=MK[k],color=C[k],label=f"{d} (slope {s:.2f})")
    print(d,"slope",round(s,3))
ax.set_xscale("log"); ax.set_yscale("log"); ax.set_xlabel("n (number of points)"); ax.set_ylabel("h (hull size)")
ax.set_title("(a) Hull size h vs n",loc="left",color=INK,fontsize=10)
ax.legend(frameon=False); fig.tight_layout(); fig.savefig("plot_a_h_vs_n.png",dpi=200)
# (b) time vs n
algos=["graham","jarvis","cgal_default","cgal_graham_andrew","cgal_jarvis"]
fig,axs=plt.subplots(1,3,figsize=(11,3.6),sharey=True)
for ax,d in zip(axs,dists):
    for k,a in enumerate(algos):
        pts=sorted((int(r["n"]),float(r["ms"])) for r in rows if r["dist"]==d and r["algo"]==a)
        if pts: ax.plot([p[0] for p in pts],[p[1] for p in pts],marker=MK[k],color=C[k],label=a)
    ax.set_xscale("log"); ax.set_yscale("log"); ax.set_xlabel("n"); ax.set_title(d,loc="left",color=INK,fontsize=10)
axs[0].set_ylabel("time (ms)")
h,l=axs[0].get_legend_handles_labels(); fig.legend(h,l,loc="upper center",bbox_to_anchor=(0.5,0.93),ncol=5,frameon=False)
fig.suptitle("(b) Running time vs n, one panel per distribution (log–log)",x=0.01,ha="left",y=0.995,fontsize=10,color=INK)
fig.tight_layout(rect=(0,0,1,0.84)); fig.savefig("plot_b_time_vs_n.png",dpi=200)
# slopes of time
for d in dists:
    for a in algos:
        pts=sorted((int(r["n"]),float(r["ms"])) for r in rows if r["dist"]==d and r["algo"]==a and int(r["n"])>=10000)
        if len(pts)>=2: print(d,a,"time slope (n>=1e4)",round(np.polyfit(np.log10([p[0] for p in pts]),np.log10([p[1] for p in pts]),1)[0],2))
