% script para graficar las capturas y ver rápidamente que es que

% primeros ensayos del PI

[files] = dir("../mediciones/captura_PI_*.csv");

for i=1:length(files)
  name = files(i).name
  D = csvread(fullfile("..", "mediciones", name));
  try
    t = D(:,1) - D(1,1);
    T = D(:,2);
    ref = D(:,5);
    % en los últimos ensayos no hay que dividirlo por 2.2
    piy = D(:,7)/2.2;
    dc = D(:,8);
  catch
    disp("errro")
    continue
  end

  figure(1);
  plot(t, T, 'xb', t, ref, 'r');
  title(strrep(name, "_", " "))
  figure(2);
  plot(t, piy, 'r', t, dc, 'b');
  title(strrep(name, "_", " "))
  waitforbuttonpress()
end
