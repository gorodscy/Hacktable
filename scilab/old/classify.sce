//
// = Note =
// A complete version of this is in SIP, function color_classify.sci
//
// = Description = 
// Simple script for classifying an image window into Red, Green, Blue, and others.
// Should work well under different lighting conditions and is robust to wrong white
// balance. Should be simple enough for real time applications.
//
// Author: Ricardo Fabbri <rfabbri@gmail.com>
//
// = Usage = 
//
// Input: im
// Dois modos de uso: 
//
// a) descomentar uma das linhas de imread abaixo
// e ler a imagem que voce quer, editando o nome 
//
// b) exec classify-run.sce pra rodar em varias imagens

// Unreliable cases (avoid these colors for your objects):
//
// im = imread('blue-halogen-15.jpg');
// im = imread('green-natural-04.jpg');
// im = imread('blue-halogen-20.jpg');
// im = imread('green-natural-06.jpg');

// median is a little better:

r = median(im(:,:,1));
g = median(im(:,:,2));
b = median(im(:,:,3));

//r = mean(im(:,:,1));
//g = mean(im(:,:,2));
//b = mean(im(:,:,3));

//im = rgb2hsv(im);
hsv = rgb2hsv([r g b]);

hue = hsv(1);
sat = hsv(2);
val = hsv(3);

//clear im;

hue = hue * 360;


if val < 0.2 & sat < 0.8
  disp 'black';
  return;
elseif val > 0.8 & sat < 0.1
  disp 'white';
  return;
end

// At this point we have
// val > 0.2 | (val < 0.8 | sat > 0.1)

if hue < 30 | hue > 330
  disp 'red';
elseif hue > 90 & hue < 150
  disp 'green';
elseif hue > 185 & hue < 270
  disp 'blue';
else // disp 'unreliable color...';
  if sat < 0.5
    warning('unreliable!')
    // in the real system you just discard this estimate and use the previous
    // estimate (e.g. previous frame) at this point
  end
  if hue >= 30 & hue <= 90
    disp 'guessing yellow';
  elseif hue >= 150 & hue <= 185
    if hue >= 180
      disp 'guessing blue'
    else
      disp 'guessing blue-green'
    end
  elseif hue >= 270 & hue <= 330
    disp 'guessing purple-pink'
  end
end

// Copyright (C) 2011  Ricardo Fabbri
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// -------------------------------------------------------------------------
