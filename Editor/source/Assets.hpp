#pragma once

namespace Editor
{

struct Cmd;

void shader(const Cmd& cmd);
void mesh(const Cmd& cmd);
void spritesheet(const Cmd& cmd);
void texture(const Cmd& cmd);
void cubemap(const Cmd& cmd);
void material(const Cmd& cmd);

}