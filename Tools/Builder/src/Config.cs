namespace Builder
{

class Config
{
    public string? Name { get; set; }
    public string? Type { get; set; }
    public string? OutputDir { get; set; }
    public string? Extension { get; set; }
    public string? Compiler { get; set; }
    public bool Debug { get; set; }
    public string[]? LibsDir { get; set; }
    public string[]? Libs { get; set; }
    public string[]? Defines { get; set; }
}

}