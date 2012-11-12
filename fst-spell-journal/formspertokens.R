pdf("graphs/formspertokens.pdf", width=10, height=7)

en = read.delim("corp/en/wikipedia.formspertokens.50000000.tsv", 
                header=FALSE)
fi = read.delim("corp/fi/wikipedia.formspertokens.50000000.tsv", 
                header=FALSE)
se = read.delim("corp/se/wikipedia.formspertokens.100000.tsv",
                header=FALSE)
kl = read.delim("corp/kl/wikipedia.formspertokens.100000.tsv", 
                header=FALSE)

max_x = max(en$V1, fi$V1, se$V1, kl$V1)
max_y = max(en$V2, fi$V2, se$V2, kl$V2)
plot_colors = c("red", "green", "blue", "yellow")

plot(en$V1, en$V2, type = "l", col = plot_colors[1], xlim = c(0, max_x), 
     ylim=c(0, max_y), axes=FALSE, ann=FALSE)
lines(fi$V1, fi$V2, type = "l", lty = 2, col = plot_colors[2])
lines(se$V1, se$V2, type = "l",  col = plot_colors[3])
lines(kl$V1, kl$V2, type = "l", col = plot_colors[4])

title(main = "New word-forms in data")

box()

axis(1)
axis(2)


title(xlab = "Tokens")
title(ylab = "Wordforms")

legend(1, max_y, c("en", "fi", "se", "kl"), fill = plot_colors)
