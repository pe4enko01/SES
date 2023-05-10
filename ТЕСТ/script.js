// Получаем контейнер, в котором будет рендериться сцена
const container = document.getElementById("container");

// Создаем сцену
const scene = new THREE.Scene();
scene.background = new THREE.Color(0xffffff);

// Создаем камеру
const camera = new THREE.OrthographicCamera(-1, 1, 1, -1, 0.1, 1000);
camera.position.set(0, 0, 10);
camera.lookAt(scene.position);

// Создаем рендерер
const renderer = new THREE.WebGLRenderer();
renderer.setSize(container.offsetWidth, container.offsetHeight);
container.appendChild(renderer.domElement);

// Определяем параметры метаболов
const numMetaballs = 5;
const ballSize = 0.2;
const threshold = 1.0;
const maxSpeed = 0.02;
const acceleration = 0.0001;
const damping = 0.98;

// Создаем массивы для хранения позиций и скоростей метаболов
const positions = [];
const velocities = [];
for (let i = 0; i < numMetaballs; i++) {
  positions.push(new THREE.Vector3(
    Math.random() * 2 - 1,
    Math.random() * 2 - 1,
    0
  ));
  velocities.push(new THREE.Vector3(
    Math.random() * maxSpeed * 2 - maxSpeed,
    Math.random() * maxSpeed * 2 - maxSpeed,
    0
  ));
}

// Создаем материал метаболов
const material = new THREE.MeshBasicMaterial({
  color: 0x0080ff,
  transparent: true,
  opacity: 0.75
});

// Создаем геометрию метаболов
const geometry = new THREE.CircleGeometry(ballSize, 32);

// Создаем метаболы
const metaballs = new THREE.Group();
for (let i = 0; i < numMetaballs; i++) {
  metaballs.add(new THREE.Mesh(geometry, material));
}
scene.add(metaballs);

// Функция для обновления положения метаболов
function updateMetaballs() {
  for (let i = 0; i < numMetaballs; i++) {
    const p = positions[i];
    const v = velocities[i];
    p.add(v);
    if (p.x < -1 || p.x > 1) {
      v.x *= -1;
      p.x = Math.min(Math.max(p.x, -1), 1);
    }
    if (p.y < -1 || p.y > 1) {
      v.y *= -1;
      p.y = Math.min(Math.max(p.y, -1), 1);
    }
    v.multiplyScalar(damping);
    v.add(new THREE.Vector3(
      Math.random() * acceleration * 2 - acceleration,
      Math.random() * acceleration * 2 - acceleration,
      0
    ));
  }
}
// Функция для обновления материала метаболов на основе их положения
function updateMaterial() {
let values = "";
for (let i = 0; i < numMetaballs; i++) {
const p = positions[i];
values += vec2(${p.x.toFixed(6)}, ${p.y.toFixed(6)}), ;
}
const fragmentShader = uniform vec2 metaballs[${numMetaballs}]; uniform float threshold; void main() { float density = 0.0; for (int i = 0; i < ${numMetaballs}; i++) { vec2 diff = gl_FragCoord.xy / resolution.xy - metaballs[i]; density += 1.0 / dot(diff, diff); } gl_FragColor = density > threshold ? vec4(1.0, 1.0, 1.0, 1.0) : vec4(0.0, 0.0, 0.0, 0.0); } ;
const material = new THREE.ShaderMaterial({
uniforms: {
metaballs: { value: positions },
threshold: { value: threshold }
},
fragmentShader: fragmentShader
});
for (let i = 0; i < numMetaballs; i++) {
metaballs.children[i].material = material;
}
}

// Функция анимации
function animate() {
requestAnimationFrame(animate);
updateMetaballs();
updateMaterial();
renderer.render(scene, camera);
}

animate();