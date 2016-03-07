#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
	int msize;

	int ppos, spos;

	bool EXIT = 0;
	bool fail_shot;

	srand(time(NULL));

	printf("Choose a map size (int): ");

	scanf_s("%i", &msize);
	getchar();

	system("CLS");

	int* hidd_map = (int*)calloc(((msize + 1) * (msize + 1)) + 1, 4);

	int* hit_map = (int*)calloc(((msize + 1) * (msize + 1)) + 1, 4);

	char* map = (char*)calloc(((msize + 1) * (msize + 1)) + 1, 1);

	map[sizeof(map)] = 0;

	for (int i = 0; i < ((msize + 1) * (msize + 1)); i++) {
		if (i < msize || i >(msize + 1) * msize || i % msize == 1 || i % msize == 0)
			map[i] = '!';
		else
			map[i] = ' ';
	}

	for (int n_ship = 0; n_ship < 4; n_ship++) {
		do {
			spos = rand() % ((msize + 1) * (msize + 1));
		} while (map[spos] != ' ' && map[spos] == '!');

		for (int ssize = 0; ssize <= n_ship; ssize++) {
			if (map[spos + n_ship] == ' ' && map[spos + n_ship] != '!')
				map[spos + ssize] = 'A' + n_ship;
		}
	}

	do {
		ppos = rand() % ((msize + 1) * (msize + 1));
	} while (map[ppos] != ' ');

	while (!EXIT) {

		for (int visiony = -2 * msize; visiony < msize; visiony += msize) {
			for (int visionx = -1; visionx < 2; visionx++) {
				hidd_map[ppos + visionx + visiony + msize] = 1;
			}
		}

		for (int j = 0; j < (msize + 1) * (msize + 1); j++) {

			if (j == ppos)
				printf("@ ");
			else if (hit_map[j] == 1)
				printf("- ");
			else if (!hidd_map[j])
				printf("* ");
			else if (hit_map[j] == 2)
				printf("x ");
			else
				printf("%c ", map[j]);

			if (!(j % msize) && j)
				printf("\n");

		}

		printf("Move (w/a/s/d):\nShoot (t/f/g/h):\nQuit (q): ");

		switch (getchar())
		{
		case 'w': if (map[ppos - msize] == ' ')
			ppos -= (msize);
			break;
		case 's': if (map[ppos + msize] == ' ')
			ppos += (msize);
			break;
		case 'a': if (map[ppos - 1] == ' ')
			ppos--;
			break;
		case 'd': if (map[ppos + 1] == ' ')
			ppos++;
			break;
		case 't': 
			fail_shot = 1;
			for (int shot = 0; shot < 3; shot++) {
				hidd_map[ppos - shot * msize] = 1;
				if (map[ppos - shot * msize] >= 'A' && map[ppos - shot * msize] <= 'Z') {
					hit_map[ppos - shot * msize] = 1;
					map[ppos - shot * msize] = ' ';
					fail_shot = 0;
				}
			}
			if (fail_shot)
				hit_map[ppos - 2 * msize] = 2;
			
			break;
		case 'g': 
			fail_shot = 1;
			for (int shot = 0; shot < 3; shot++) {
				hidd_map[ppos + shot * msize] = 1;
				if (map[ppos + shot * msize] >= 'A' && map[ppos + shot * msize] <= 'Z') {
					hit_map[ppos + shot * msize] = 1;
					map[ppos + shot * msize] = ' ';
					fail_shot = 0;
				}
			}
				if (fail_shot)
					hit_map[ppos + 2 * msize] = 2;
			break;

		case 'f': 
			fail_shot = 1;
			for (int shot = 0; shot < 3; shot++) {
				hidd_map[ppos - shot] = 1;
				if (map[ppos - shot] >= 'A' && map[ppos - shot] <= 'Z') {
					hit_map[ppos - shot] = 1;
					map[ppos - shot] = ' ';
					fail_shot = 0;
				}
			}
			if (fail_shot)
				hit_map[ppos - 2] = 2;
			break;

		case 'h': 
			fail_shot = 1;
			for (int shot = 0; shot < 3; shot++) {
				hidd_map[ppos + shot] = 1;
				if (map[ppos + shot] >= 'A' && map[ppos + shot] <= 'Z') {
					hit_map[ppos + shot] = 1;
					map[ppos + shot] = ' ';
					fail_shot = 0;
				}
			}

			if (fail_shot)
				hit_map[ppos + 2] = 2;
			break;

		case 'q': EXIT = 1;
			break;
		}

		system("CLS");

	}


	free(map);
	free(hidd_map);
	free(hit_map);

	getchar();
	return 0;
}