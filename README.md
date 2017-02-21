## 简介

bitmapConvorter项目是对bitmap颜色量化的研究与实现，实现了4bpp，8bpp，16bpp，24bpp，32bpp之间的互相转换。

其中4bpp与8bpp的转换采用了8叉树的算法来提取主题色生成调色盘。在8bpp转换时效果良好。

16bpp通过舍去低位将RGB888转换为RGB565，但是实现效果不是很理想，偏色比较明显。也许应该在转换之前先靠色。

4bpp转换时发生了奇怪的现象，如果原图片色彩较少时，转换一切正常，但如果原图色彩较丰富时，图片就会出现莫名的扭曲。也许应该考虑采取其他的颜色量化算法。

## 用法
usage: [-i infile] [-b bitCount] [-o outfile] [-g] [-h] [infile]
