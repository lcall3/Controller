// lcall3 Controller is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// lcall3 Controller is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lcall3 Controller. If not, see <http://www.gnu.org/licenses/>.

// This javascript wraps the ui objects used in p5 and lcall3 controller web app

class Button {
    constructor(x, y, name, handler) {
        this.x = x;
        this.y = y;
        this.name = name;
        this.width = width - 2 * this.x;
        this.height = 60;
        this.enabled = true;
        this.handler = handler;
        this.size = 20;
    }

    draw() {
        rectMode(CORNER);
        var btnColor;
        if (this.enabled) {
            btnColor = color('#FFF');
        } else {
            btnColor = color('#444');
        }
        stroke(btnColor);
        noFill();
        rect(this.x, this.y, this.width, this.height);
        fill(btnColor);
        noStroke();
        textAlign(CENTER, CENTER);
        textSize(this.size);
        text(this.name, this.x + this.width / 2, this.y + this.height / 2);
    }

    callHandler() {
        this.handler();
    }

    isMouseInside(x, y) {
        if (x > this.x && y > this.y && x < this.x + this.width && y < this.y + this.height) {
            return true;
        } else {
            return false;
        }
    }

    setEnable(enable) {
        this.enable = enable;
    }

    setXY(x, y) {
        this.x = x;
        this.y = y;
    }

    setWidth(w) {
        this.width = w;
    }

    setHeight(h) {
        this.height = h;
    }
}