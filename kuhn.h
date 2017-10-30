#define ROW 0
#define COL 1

template <typename T, int S, T INF>
void kuhn_augment(
    int const n, T const g[S][S], int rig[S], int lef[S],
    T v[2][S], int c[2][S], int x[S]) {
  T t = INF;
  for (int i = 1; i <= n; i++) if (!c[ROW][i])
    for (int j = 1; j <= n; j++) if (!c[COL][j])
      t = min(t, g[i][j] - v[ROW][i] - v[COL][j]);

  for (int i = 1; i <= n; i++)
    v[ROW][i] -= t * c[ROW][i],
    v[COL][i] += t * !c[COL][i];

  for (int i = 1; i <= n; i++) if (!c[ROW][i])
    for (int j = 1; j <= n; j++) if (!c[COL][j])
      if (g[i][j] - v[ROW][i] - v[COL][j] == 0)
        if (rig[i]) {
          x[i] = j; c[COL][rig[i]] = !(c[ROW][i] = 1);
          break;
        } else {
          while (i) rig[i] = j, lef[j] = lef[j] + i - (i = lef[j]), j = x[i];
          return;
        }

  kuhn_augment<T, S, INF>(n, g, rig, lef, v, c, x);
}

template <typename T, int S, T INF>
void kuhn(int const n, T const g[S][S], int rig[S], int lef[S]) {
  memset(rig, 0, S * sizeof(T));
  memset(lef, 0, S * sizeof(T));

  T t, v[2][S];
  for (int i = 1; i <= n; i++) {
    t = INF; for (int j = 1; j <= n; j++) t = min(t, g[i][j]); v[ROW][i] = t;
    t = INF; for (int j = 1; j <= n; j++) t = min(t, g[j][i]); v[COL][i] = t;
  }

  int c[2][S]; int x[S];
  for (int step = 1; step <= n; step++) {
    memset(c[ROW], 0, sizeof c[ROW]);
    memcpy(c[COL], lef, sizeof c[COL]);
    kuhn_augment<T, S, INF>(n, g, rig, lef, v, c, x);
  }

  for (int i = 1; i <= n; i++)
    if (g[i][rig[i]] == INF) rig[i] = lef[rig[i]] = 0;
}
