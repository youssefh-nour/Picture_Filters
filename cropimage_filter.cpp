void cropimage(Image& img, int startx, int starty, int new_wid, int new_h) {
	Image cropped_img(new_wid, new_h);
	for (int i = 0;i < new_wid;++i) {
		for (int j = 0;j < new_h;++j) {
			for (int k = 0;k < 3;++k) {
				cropped_img(i, j, k) = img(startx + i, starty + j, k);
			}
		}
	}
	img = cropped_img;
}
