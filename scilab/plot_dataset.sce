// se quiser, insira o caminho pras imagens aqui
mypath="/home/rfabbri/lib/pics/test-imgs/color-webcam-db/lenovo/";

// precomputed medians
has_medians=%t;
fmedians=mypath + 'medians.dat';
if has_medians
  load(fmedians,'medians');
end

fs = ls(mypath+'*.jpg');

id_red = 1;
id_green = 2;
id_blue = 3;
id_black = 4;
id_yellow = 5;
id_white = 6;


cmap = zeros(6,3);
cmap(id_red,:) = [1 0 0];
cmap(id_green,:) = [0 1 0];
cmap(id_blue,:) = [0 0 1];
cmap(id_black,:) = [0 0 0];
cmap(id_yellow,:) = [1 1 0];
cmap(id_white,:) = [1 1 1];

nimgs = size(fs,1);

colors = zeros(nimgs,1);

for i=1:nimgs
  true_class=unix_g('echo ' + basename(fs(i)) + '|grep -o ^[^\/-]*-|grep -o [^-]*');
    select true_class
    case 'red'
      colors(i) =  id_red;
    case 'green'
      colors(i) =  id_green;
    case 'blue'
      colors(i) =  id_blue;
    case 'black'
      colors(i) =  id_black;
    case 'yellow'
      colors(i) =  id_yellow;
    case 'white'
      colors(i) =  id_white;
    else
      error('Invalid color class returned for ' + string(i) + ', ' + string(j));
    end
end

// scatterplot bogus.
clf;
xset('colormap', cmap);
param3d1(medians(:,1)', medians(:,2)', list(medians(:,3)',colors'-1));
e = gce();
e.line_mode = "off";
e.mark_mode = "on";
xset('colormap', cmap);
