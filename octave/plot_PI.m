% script para graficar las capturas y ver rápidamente que es que

[files] = dir("captura_*.csv");

for i=1:length(files)
  name = files(i).name
  D = csvread(name);
  t = D(:,1) - D(1,1);
  T = D(:,2);
  ref = D(:,5);
  piy = D(:,7);
  dc = D(:,8);

  figure(1);
  plot(t, T, 'xb', t, ref, 'r');
  title(name)
  figure(2);
  plot(t, piy, 'r', t, dc, 'b');
  title(name)
  waitforbuttonpress()
end