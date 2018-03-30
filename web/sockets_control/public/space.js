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

// This contains function that transform between screen space,
// laser space, normalized space etc.

class Space {
    constructor(boundSize) {
        this.boundSize = boundSize;

        this.yawMin = -100;
        this.yawMax = 100;
        this.pitchMin = -50;
        this.pitchMax = 50;
    }

    // Set yaw and pitch parameters
    setYawPitchParams(yawMin, yawMax, pitchMin, pitchMax) {
        this.yawMin = yawMin;
        this.yawMax = yawMax;
        this.pitchMin = pitchMin;
        this.pitchMax = pitchMax;
    }

    // Screen coords to normalized spaces
    screenToNorm(screen) {
        var a = -boundSize / 2;
        var b = a * -1;
        return createVector(
            constrain(map(screen.x, a, b, -1, 1), -1 ,1),
            constrain(map(screen.y, a, b, -1, 1), -1, 1)
        );
    }

    // Normalized coords to screen space
    normToScreen(norm) {
        var a = -boundSize / 2;
        var b = a * -1;
        return createVector(
            map(norm.x, -1, 1, a, b),
            map(norm.y, -1, 1, a, b)
        );
    }

    // Normalized coords to laser space
    normToLaser(norm) {
        return createVector(
            map(norm.x, -1, 1, this.yawMin, this.yawMax),
            map(norm.y, -1, 1, this.pitchMin, this.pitchMax)
        );
    }
}