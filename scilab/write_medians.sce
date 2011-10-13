
// Para rodar:
// - primeiro ponha o caminho pra base de dados em mypath abaixo
// - execute este script no scilab
// - precisa do SIP
//
// Talvez voce queira a saida num arquivo, neste caso entre no scilab assim:
//
// scilab -nw | tee saida.txt
//
stacksize(20000000);
sip_quiet;
//sip_wordy;

// se quiser, insira o caminho pras imagens aqui
mypath="/home/rfabbri/lib/pics/test-imgs/color-webcam-db/lenovo/easy/";

// hard!:
//mypath="/home/rfabbri/lib/pics/test-imgs/color-webcam-db/lenovo/";

//mypath="./"
fs = ls(mypath+'*.jpg');

nimgs = size(fs,1);

medians = zeros(nimgs,3);
for i=1:nimgs
  RGB = imread(fs(i));

  medians(i,1) = median(RGB(:,:,1));
  medians(i,2)  = median(RGB(:,:,2));
  medians(i,3) = median(RGB(:,:,3));
end

save(mypath+'medians.dat', medians);
