# pipex

UNIX 매커니즘을 자세히 알아보자

## HOW TO
<pre>
<code>
./pipex file1 cmd1 cmd2 file2
</code>
</pre>

##example
<pre>
<code>
./pipex infile ``ls -l'' ``wc -l'' outfile
</code>
</pre>
`< infile ls -l | wc -l > outfile의 결과와 동일해야함`


|제목|설명|
|------|---|
|execve|다른 프로그램을 실행하고 자신을 종료|
|int dup(int fd)|파일 식별자를 복제|
|int dup2(int old_fd1, int new_fd2)|fd2를 fd1으로 바꿈|
