// se quiser, insira o caminho pras imagens aqui
mypath="/home/rfabbri/lib/pics/test-imgs/color-webcam-db/lenovo/easy/";

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
cmap(id_yellow,:) = [0.7 0.7 0.2];
cmap(id_white,:) = [0.6 0.6 0.6];

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

clf;
drawlater
xset('colormap', cmap);
param3d1([medians(:,1)'; medians(:,1)'], [medians(:,2)'; medians(:,2)'], ...
  [medians(:,3)'; medians(:,3)']);

xlabel 'R';
ylabel 'G';
zlabel 'B';

e = gce();

e.children.mark_mode = "on";
e.children.mark_size_unit = "point";
e.children.mark_size = 8;

for i=1:nimgs
  e.children(i).mark_foreground = colors(i);
end
drawnow

xset('colormap', cmap);



// histograms

nclasses = size(cmap,1);

for i=1:nclasses
  // locate all the e.g. 'reds' in medians
  ids=find(colors == i);
  d = medians(ids,:);

  figure;
  clf;
  histplot(40,d(:,1))
  xtitle 'R'

  figure;
  clf;
  histplot(40,d(:,1))
  xtitle 'G'

  figure;
  clf;
  histplot(40,d(:,1))
  xtitle 'B'
end
