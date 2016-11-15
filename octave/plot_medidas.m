% script para graficar las capturas y ver rápidamente que es que

[files] = dir("../mediciones/captura_continua*.csv");

for i=1:length(files)
  name = files(i).name
  D = csvread(fullfile("..", "mediciones", name));
  try
    t = D(:,1) - D(1,1);
    T = D(:,2);
    ref = D(:,9);
    piy = D(:,7);
    dc = D(:,8);
  catch
    disp("errro")
    continue
  end

  figure(1);
  plot(t, T, 'xb', t, ref, 'r');
  title(name)
  figure(2);
  plot(t, piy, 'r', t, dc, 'b');
  title(name)
  waitforbuttonpress()
end
