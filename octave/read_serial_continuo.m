% Script de Octave para leer y graficar datos desde el puerto serial.

serial_init

% creamos nuestras figuras
clf
subplot(3, 1, 1);
h1 = plot(1, 1, 'xb;temperatura;');
legend('location', 'northwest');
hold on
h2 = plot(1, 1, '-r;referencia;');
grid on
subplot(3, 1, 2);
h3 = plot(1, 1, '-r;salida PI;');
legend('location', 'northwest');
hold on
h4 = plot(1, 1, '-b;salida PI (saturacin);');
grid on
subplot(3, 1, 3);
h5 = plot(1, 1, '-b;ciclo de trabajo;');
legend('location', 'northwest');
grid on

log = fopen("registro.log", "a");
fwrite(log, sprintf("-Inicio del registro de captura %s\r\n", fecha()));

srl_write(fd, "cP"); % iniciar captura
Tm = 1; % en este modo el muestreo es cada seg
if (exist("i", "var"))
  i = length(t);
 else
  i = 1;
end
%clear t temp ref piy piys dc
unwind_protect
  while(1)
    % leemos una línea
    str = read_linea(fd);
    try
      [n, T, Tth, Tlm, ADth, ADlm, DC, REF, PIx, PIy ] = strread(str, 
            "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f");
    catch
      continue
    end
    t(i) = n * Tm;
    temp(i) = T;
    tempth(i) = Tth;
    templm(i) = Tlm;
    ref(i) = REF;
    dc(i) = DC*100;
    piy(i) = PIy;
    piys(i) = DC*220;
    pix(i) = PIx;
    % actualizar gráfico
    set(h1, 'XData', t, 'YData', temp);
    set(h2, 'XData', t, 'YData', ref);
    set(h3, 'XData', t, 'YData', piy);
    set(h4, 'XData', t, 'YData', piys);
    set(h5, 'XData', t, 'YData', dc);
    drawnow;
    %guardamos un registro
    fwrite(log, str);
    i++;
    % hacemos una pausa proporcional al muestreo así no estamos esperando mucho 
    % en srl_read que dificulta terminar el script con ctrl-c
    pause(Tm*0.8);
  end
unwind_protect_cleanup
  % Ctrl-C, detener y cerrar la conección
  srl_write(fd, "cP");
  fclose(fd);
  fwrite(log, sprintf("-Fin de la captura %s\r\n", fecha()));
  fclose(log);
  % guardar los datos capturados
  % antes de guardar las longitudes tienen que ser iguales
  N = length(pix);
  t = t(1:N);
  temp = temp(1:N);
  piy = piy(1:N);
  ref = ref(1:N);
  pix = pix(1:N);
  dc = dc(1:N);
  templm = templm(1:N);
  tempth = tempth(1:N);
  csvwrite(sprintf("captura_continua_%s.csv", fecha()),
      [t' temp' tempth' templm' ref' pix' piy' dc']);
  printf("captura guardada\n")
end
